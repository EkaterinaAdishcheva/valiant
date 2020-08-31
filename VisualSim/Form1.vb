Imports System.Threading
Imports System.Text.RegularExpressions
Imports System.Text

Enum simMode
    smNull = 0
    smOne = 1
    smBulk = 10
    smBulkRunning = 11
    smBulkAborted = 12
    smBulkCalculated = 13
    smBulkResults = 14
End Enum

Public Class Form1
    Public Structure FLASHWINFO
        Public cbSize As UInt32
        Public hwnd As IntPtr
        Public dwFlags As UInt32
        Public uCount As UInt32
        Public dwTimeout As UInt32
    End Structure
    Private Declare Function FlashWindowEx Lib "User32" (ByRef fwInfo As FLASHWINFO) As Boolean
    Private Declare Function GetActiveWindow Lib "user32" () As Long

    Private Declare Function SimReload Lib "SlotsSimulator.dll" _
        Alias "reload_settings" () As Int32

    Private Declare Function OneSpinRun Lib "SlotsSimulator.dll" _
        Alias "one_spin_run" () As Int32
    Private Declare Function BulkRun Lib "SlotsSimulator.dll" _
        Alias "bulk_run" (ByVal NumSpins As UInt64, ByVal thread_id As Int32) As Int32
    Private Declare Function BulkAggStats Lib "SlotsSimulator.dll" _
        Alias "bulk_agg_stat" () As Int32
    Private Declare Function GetMaxThreads Lib "SlotsSimulator.dll" _
        Alias "get_max_threads" () As Int32
    Private Declare Function BulkLog Lib "SlotsSimulator.dll" _
        Alias "bulk_log_results" (ByVal filename As StringBuilder, ByVal MaxLen As Int32,
                                  ByVal gamename As StringBuilder, ByVal NameLen As Int32) As Int32

    Private Declare Function GetScatterSymbol Lib "SlotsSimulator.dll" _
        Alias "get_symbol" (ByVal ReelNo As Int32, ByVal LineNo As Int32) As Int32
    Private Declare Function GetCellTag Lib "SlotsSimulator.dll" _
        Alias "get_cell_tag" (ByVal ReelNo As Int32, ByVal LineNo As Int32) As Int32
    Private Declare Function GetSpinMessage Lib "SlotsSimulator.dll" _
        Alias "get_spin_message" (ByVal message As StringBuilder, ByVal MaxLen As Int32) As Int32

    Private Declare Function GetTotalPaid Lib "SlotsSimulator.dll" _
        Alias "get_total_paid" () As UInt64
    Private Declare Function GetTotalWin Lib "SlotsSimulator.dll" _
        Alias "get_total_win" () As UInt64
    Private Declare Function GetLastWin Lib "SlotsSimulator.dll" _
        Alias "get_spin_win" () As UInt64
    Private Declare Function ResetSimulator Lib "SlotsSimulator.dll" _
        Alias "reset_sim_arr" () As Int32

    Private Declare Function GetWinLineSymbol Lib "SlotsSimulator.dll" _
        Alias "win_line_symbol" (ByVal LineIdx As Int32) As Int32
    Private Declare Function WinLineIsWin Lib "SlotsSimulator.dll" _
        Alias "win_line_is_win" (ByVal LineIdx As Int32) As Int32
    Private Declare Function GetWinLineLen Lib "SlotsSimulator.dll" _
        Alias "win_line_length" (ByVal LineIdx As Int32) As Int32
    Private Declare Function GetWinLineValue Lib "SlotsSimulator.dll" _
        Alias "win_line_value" (ByVal LineIdx As Int32) As UInt64
    Private Declare Function GetWinLineWhere Lib "SlotsSimulator.dll" _
        Alias "win_line_where" (ByVal LineIdx As Int32, ByVal ReelNo As Int32) As Int32
    Private Declare Function GetWinLineMaxCount Lib "SlotsSimulator.dll" _
        Alias "get_win_line_maxcount" () As Int32

    Private Declare Function GetScatterWin Lib "SlotsSimulator.dll" _
        Alias "get_scatter_win" () As Int32
    Private Declare Function GetScatterCount Lib "SlotsSimulator.dll" _
        Alias "get_scatters_count" () As Int32


    Private Declare Function GetFreeWin Lib "SlotsSimulator.dll" _
        Alias "get_free_spin_win" () As UInt64
    Private Declare Function GetFreeSpinsNum Lib "SlotsSimulator.dll" _
        Alias "get_free_spin_order" () As UInt64

    Private Declare Function GetRTP Lib "SlotsSimulator.dll" _
        Alias "get_rtp" () As Double
    Private Declare Function GetHitRate Lib "SlotsSimulator.dll" _
        Alias "get_hit_rate" () As Double
    Private Declare Function GetGamesCount Lib "SlotsSimulator.dll" _
        Alias "get_games_count_arr" () As UInt64
    Private Declare Function GetWidth Lib "SlotsSimulator.dll" _
        Alias "get_width" () As Int32
    Private Declare Function GetHeight Lib "SlotsSimulator.dll" _
        Alias "get_height" (ByVal reel As Int32) As Int32
    Private Declare Function GetSpinType Lib "SlotsSimulator.dll" _
        Alias "get_spin_type" () As Int32
    Private Declare Function GetNextSpinType Lib "SlotsSimulator.dll" _
        Alias "get_spin_type_next" () As Int32
    Private Declare Function SetBet Lib "SlotsSimulator.dll" _
        Alias "set_bet" (ByVal Bet As Int32) As Int32
    Private Declare Function GetBalance Lib "SlotsSimulator.dll" _
        Alias "get_balance" () As Int64
    Private Declare Function SetBalance Lib "SlotsSimulator.dll" _
        Alias "set_balance" (ByVal Balance As UInt64) As Int32
    Private Declare Function GetAwardedFreeSpins Lib "SlotsSimulator.dll" _
        Alias "get_awarded_free_spins" () As UInt64

    Private brd As Long = 10
    Private lwd As Long = 5
    Private crc As Long = 7

    Private WindowTitlePrefix As String
    Private GameName As String
    Private GameName_1 As StringBuilder
    Private LogPrefix As String = "Log"
    Private SpinTypeName(10) As String
    Private SpinTypeShowOrder(10) As Boolean
    Private SpinTypeShowCount(10) As Boolean
    Private WaitThis As Boolean

    Private MaxThreads As Long
    Private mode As simMode
    Private interactive As Boolean
    Private flashing As Boolean = True
    Private repertoir(200) As String
    Private repertoir_type(200) As String

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.AcceptButton = btOne
        Me.CancelButton = btOk

        mode = simMode.smNull

        WindowTitlePrefix = Me.Text + ": "
        MaxThreads = Environment.ProcessorCount

        LoadReelSymbols()
        LoadVisualParams()

        interactive = True
        If Environment.GetCommandLineArgs().Count > 1 Then
            Dim j As Long

            j = Array.IndexOf(Environment.GetCommandLineArgs(), "-n")
            If j > 0 Then
                Dim NumGames As String = Environment.GetCommandLineArgs().GetValue(j + 1)
                Dim multiplier As Long = 1
                If NumGames.ToUpper().Last = "M" Then
                    multiplier = 1000000
                    NumGames = NumGames.Substring(0, NumGames.Length - 1)
                ElseIf NumGames.ToUpper().Last = "K" Then
                    multiplier = 1000
                    NumGames = NumGames.Substring(0, NumGames.Length - 1)
                End If
                txtNumGames.Text = CLng(NumGames) * multiplier
            End If
                j = Array.IndexOf(Environment.GetCommandLineArgs(), "-thr")
            If j > 0 Then
                MaxThreads = CLng(Environment.GetCommandLineArgs().GetValue(j + 1))
            End If

            If Environment.GetCommandLineArgs().Contains("-run") Then
                interactive = False
                btBulk_Click(Nothing, Nothing)
            ElseIf Environment.GetCommandLineArgs().Contains("-start") Then
                btBulk_Click(Nothing, Nothing)
            End If
        End If
    End Sub
    Private Sub btOk_Click(sender As Object, e As EventArgs) Handles btOk.Click
        Me.Close()
    End Sub
    Private Sub LoadVisualParams()
        WaitThis = False
        Dim lines() As String = IO.File.ReadAllLines("visual.txt")
        For Each line As String In lines
            ' To fix: remove code duplication
            line = Regex.Replace(line, "^\s+", "")
            line = Regex.Replace(line, "#.*", "")
            line = Regex.Replace(line, ";.*", "")
            line = Regex.Replace(line, "//.*", "")
            line = Regex.Replace(line, "[,.=]", "")
            If line <> "" Then
                Dim matches() As String = line.Split(":")
                If matches(0) = "Name" Then
                    GameName = matches(1)
                    Me.Text = WindowTitlePrefix & GameName
                    GameName_1 = New StringBuilder(GameName)
                ElseIf matches(0) = "SpinTypes" Then
                    Dim SpinTypes As Long = CLng(matches(1))
                    ' Hiding "wait bonus" checks
                    checkBonus1.Visible = (SpinTypes > 1)
                    checkBonus2.Visible = (SpinTypes > 2)
                    checkBonus3.Visible = (SpinTypes > 3)
                    checkBonus4.Visible = (SpinTypes > 4)
                ElseIf matches(0) = "SpinType" Then
                    Dim SpinType As Long = CLng(matches(1))
                    SpinTypeName(SpinType) = matches(2)
                    SpinTypeShowOrder(SpinType) = (matches(3) = "Y")
                    SpinTypeShowCount(SpinType) = (matches(4) = "Y")
                ElseIf matches(0) = "LogPrefix" Then
                    LogPrefix = matches(1)
                ElseIf matches(0) = "Wait" Then
                    WaitThis = Not (matches(1) = "Next")
                End If
            End If
        Next line
    End Sub
    Private Sub LoadReelSymbols()
        Dim lines() As String = IO.File.ReadAllLines("ReelSymb.txt")
        For Each line As String In lines
            line = Regex.Replace(line, "^\s+", "")
            line = Regex.Replace(line, "#.*", "")
            line = Regex.Replace(line, ";.*", "")
            line = Regex.Replace(line, "//.*", "")
            line = Regex.Replace(line, "[,.=]", "")
            If line <> "" Then
                Dim matches As MatchCollection = Regex.Matches(line, "(\S+)")
                Dim ind As Long
                ind = CInt(matches(1).Value)
                If ind >= 0 Then
                    repertoir(ind) = matches(0).Value
                    repertoir_type(CInt(matches(1).Value)) = matches(2).Value
                End If
            End If
        Next
    End Sub

    Dim thread2 As Thread
    Dim thread2_ok As Boolean
    Dim btBulk_Text As String
    Private Sub btBulk_Click(sender As Object, e As EventArgs) Handles btBulk.Click
        If mode < simMode.smBulk Then
            gbOneGame1.Visible = False
            gbOneGame2.Visible = False
            picScatter.Visible = False
            lblThisIsFreeSpin.Visible = False
            btnRereadSettings.Visible = False

            ResetSimulator()
        End If
        gbBulk.Visible = False
        SetBet(CLng(txtBet.Text))

        If thread2 Is Nothing Then
            thread2_ok = True
            thread2 = New Thread(AddressOf BulkRunTask)
            thread2.IsBackground = True
            thread2.Name = "Bulk Manager"
            mode = simMode.smBulkRunning
            thread2.Start()
        Else
            interactive = True
            thread2_ok = False
            thread2.Abort()
            thread2.Join()
            BulkFinish()
        End If
    End Sub
    Private Sub BulkRunTask()
        BulkStart()
        Dim NumGames As Long
        NumGames = CLng(txtNumGames.Text)

        If NumGames <= 2000 Then
            BulkRun(NumGames, 0)
        Else
            Dim threads As Long = MaxThreads
            If threads > 1 Then
                If threads > GetMaxThreads() Then
                    threads = GetMaxThreads()
                End If
            End If
            If threads <= 0 Then
                threads = 1
            End If
            Dim thr() As Thread
            If threads > 1 Then
                ReDim thr(threads - 2)
            End If

            Dim NumGames1 As Long = Math.Floor(NumGames / 100 / threads)
            Dim NumGames100 As Long = NumGames - (100 * threads - 1) * NumGames1
            For j = 1 To 100
                If threads > 1 Then
                    For t = 0 To threads - 2
                        thr(t) = New Thread(Sub(ByVal id As Object) BulkRun(NumGames1, CLng(id)))
                        thr(t).Name = "Worker " & t
                        thr(t).IsBackground = True
                        thr(t).Start(t)
                    Next
                End If
                ' The last chunk for every iteration
                ' is executed in the 'manager' thread
                If j < 100 Then
                    BulkRun(NumGames1, threads - 1)
                Else
                    BulkRun(NumGames100, threads - 1)
                End If

                If threads > 1 Then
                    For t = 0 To threads - 2
                        thr(t).Join()
                        thr(t) = Nothing
                    Next
                End If

                txtProgress.Invoke(
                        Sub() txtProgress.Text = "Spin: " & GetGamesCount().ToString("N0") _
                            & " RTP: " & Format(GetRTP(), "0.00") & "%")
                txtTechInfo.Invoke(
                        Sub() txtTechInfo.Text = "Threads: " & CStr(threads))

                If Not thread2_ok Then
                    BulkFinish()
                    Exit Sub
                End If
                Dim val1 As Long
                val1 = j
                prBulk.Invoke(Sub() prBulk.Value = val1)
            Next j ' Outer loop for bulk processing
            If threads > 1 Then
                txtTechInfo.Invoke(Sub() txtTechInfo.Text = "Aggregating...")
                BulkAggStats()
            End If
        End If

        Dim LogFileName As StringBuilder
        LogFileName = New StringBuilder(100)
        LogFileName.Append(LogPrefix)
        txtTechInfo.Invoke(Sub() txtTechInfo.Text = "Writing log...")
        BulkLog(LogFileName, LogFileName.Capacity, GameName_1, GameName_1.Capacity)
        lblLogFileName.Text = "Saved log to " & LogFileName.ToString()
        mode = simMode.smBulkCalculated
        BulkFinish()
    End Sub
    Private Sub BulkStart()
        btBulk_Text = btBulk.Text
        Invoke(Sub()
                   btBulk.Text = "Abort"
                   prBulk.Visible = True
                   txtProgress.Visible = True
                   txtProgress.Text = ""
                   txtTechInfo.Visible = True
                   txtTechInfo.Text = ""
                   prBulk.Value = 0
                   btOne.Enabled = False
                   btnReset.Enabled = False
               End Sub)
    End Sub
    Private Sub BulkFinish()
        Invoke(Sub()
                   btBulk.Text = btBulk_Text
                   prBulk.Visible = False
                   txtProgress.Visible = False
                   txtTechInfo.Visible = False
                   btOne.Enabled = True
                   btnReset.Enabled = True

                   If GetActiveWindow() <> Me.Handle Then
                       Dim fwi As New FLASHWINFO
                       With fwi
                           .hwnd = Me.Handle
                           .dwFlags = 2 + 12
                           .uCount = 0
                           .dwTimeout = 0 ' Use the default cursor blink rate.
                           .cbSize = CUInt(System.Runtime.InteropServices.Marshal.SizeOf(fwi))
                       End With

                       flashing = FlashWindowEx(fwi)
                   End If

               End Sub)
        thread2 = Nothing
        If mode = simMode.smBulkCalculated Then
            If interactive Then
                Invoke(Sub() BulkShowResults())
                mode = simMode.smBulkResults
            Else
                Me.Close()
            End If
        Else
            mode = simMode.smBulkAborted
            doReset()
        End If
    End Sub
    Private Sub BulkShowResults()
        gbBulk.Visible = True
        txtBulkGames.Text = GetGamesCount().ToString("N0")
        txtBulkWin.Text = GetTotalWin().ToString("N0")
        txtBulkRTP.Text = Format(GetRTP(), "0.00") & "%"
        txtBulkHitRate.Text = Format(GetHitRate(), "0.00") & "%"

        lblSaved.Visible = False
    End Sub

    Dim WinLinesRef(5000) As Long
    Dim WinLinesType(5000) As Long
    Dim SelectedWinLine As Long
    Dim SelectedWinLineType As Long
    Private Sub btOne_Click(sender As Object, e As EventArgs) Handles btOne.Click
        If mode <> simMode.smOne Then
            gbOneGame1.Visible = True
            gbOneGame2.Visible = True
            gbBulk.Visible = False
            picScatter.Visible = True
            prBulk.Visible = False
            txtProgress.Visible = False
            txtTechInfo.Visible = False
            btnReset.Enabled = True
            btnRereadSettings.Visible = False

            ResetSimulator()
            SetBalance(CLng(txtStartBalance.Text))

            mode = simMode.smOne
        End If
        SetBet(CLng(txtBet.Text))

        Dim wait(10) As Boolean
        wait(1) = checkBonus1.Checked
        wait(2) = checkBonus2.Checked
        wait(3) = checkBonus3.Checked
        wait(4) = checkBonus4.Checked
        wait(5) = False
        wait(6) = False
        wait(7) = False
        wait(8) = False
        wait(9) = False
        wait(10) = False
        Dim wait_win As Long
        wait_win = 0
        If txtWaitWin.Text <> "" Then
            wait_win = CLng(txtWaitWin.Text)
        End If
        Dim waiting_on As Boolean
        waiting_on = wait_win > 0
        For j = 1 To 10
            waiting_on = waiting_on Or wait(j)
        Next


        Dim limit_wait As Long = 1000000
        Dim waited As Long = limit_wait

        If waiting_on Then
            Dim run As Boolean
            Dim game_type As Long
            run = True
            While run
                OneSpinRun()
                If WaitThis Then
                    game_type = GetSpinType()
                Else
                    game_type = GetNextSpinType()
                End If
                run = wait_win = 0 Or GetLastWin() < wait_win
                For j = 1 To 10
                    run = run And Not (wait(j) And game_type = j)
                Next
                waited = waited - 1
                run = run And waited > 0
            End While
            checkBonus1.Checked = False
            checkBonus2.Checked = False
            checkBonus3.Checked = False
            checkBonus4.Checked = False
        Else
            OneSpinRun()
        End If

        txtTotalWin.Text = GetTotalWin()
        txtThisWin.Text = GetLastWin()
        txtRTP.Text = Format(GetRTP(), "0.00") & "%"
        txtTotalSpins.Text = GetGamesCount()
        txtBalance.Text = GetBalance()
        txtFreeWin.Text = GetFreeWin()

        Dim SpinType As Long = GetSpinType()

        Dim message As String
        Dim idx As Long
        message = ""
        If SpinType <> 0 Then
            message = message & SpinTypeName(SpinType)
            If SpinTypeShowOrder(SpinType) Then
                message = message & " (" & GetFreeSpinsNum()
                If SpinTypeShowCount(SpinType) Then
                    message = message & " / " & GetAwardedFreeSpins()
                End If
                message = message & ")"
            End If
        End If
        Dim spin_message1 As New StringBuilder(100)

        If GetSpinMessage(spin_message1, spin_message1.Capacity) <> 0 Then
            Dim spin_message As String = spin_message1.ToString()
            Dim matches As MatchCollection = Regex.Matches(spin_message, "{(\d+)}")
            If matches.Count > 0 Then
                idx = CInt(matches(0).Groups(1).Value)
                spin_message = Regex.Replace(spin_message, "{(\d+)}", repertoir(idx))
            End If

            message = message & " " & spin_message
        End If
        If waiting_on And waited = 0 Then
            message = message + " Waited " + CStr(limit_wait) + " :("
        End If

        If message <> "" Then
            lblThisIsFreeSpin.Text = message
            lblThisIsFreeSpin.Visible = True
        Else
            lblThisIsFreeSpin.Visible = False
        End If

        lstWinLines.Items.Clear()
        idx = 0
        For j = 0 To GetWinLineMaxCount() - 1
            If WinLineIsWin(j) Then
                lstWinLines.Items.Add(
                    GetWinLineLen(j) & " of " & repertoir(GetWinLineSymbol(j)) _
                    & " = " & GetWinLineValue(j) & " [L" & CStr(j) & "]")
                WinLinesRef(idx) = j
                WinLinesType(idx) = 1
                idx = idx + 1
            End If
        Next j
        If GetScatterWin() > 0 Then
            lstWinLines.Items.Add(GetScatterCount() & " scatters = " & GetScatterWin())
            WinLinesRef(idx) = 0
            WinLinesType(idx) = 0
            idx = idx + 1
        End If

        If idx = 0 Then
            lstWinLines.Items.Add("No win lines")
            lblWinLines.Text = "Winning lines"
            lstWinLines.Enabled = False
        Else
            lblWinLines.Text = "Winning lines (" & idx & ")"
            lstWinLines.Enabled = True
        End If
        SelectedWinLine = -1
        SelectedWinLineType = -1

        picScatter.Invalidate()
    End Sub

    Private Sub doReset()
        gbOneGame1.Visible = False
        gbOneGame2.Visible = False
        gbBulk.Visible = False
        picScatter.Visible = True
        prBulk.Visible = False
        txtProgress.Visible = False
        txtTechInfo.Visible = False
        btnReset.Enabled = False
        lblThisIsFreeSpin.Visible = False
        btnRereadSettings.Visible = True

        mode = simMode.smNull

        ResetSimulator()
        SelectedWinLine = -1

        picScatter.Invalidate()
    End Sub
    Private Sub btReset_Click(sender As Object, e As EventArgs) Handles btnReset.Click
        doReset()
        checkBonus1.Checked = False
        checkBonus2.Checked = False
        checkBonus3.Checked = False
        checkBonus4.Checked = False
        txtWaitWin.Text = ""
    End Sub

    Dim font1 As Font, font3 As Font
    Private Sub picScatter_Paint(sender As Object, e As PaintEventArgs) Handles picScatter.Paint
        e.Graphics.FillRectangle(Brushes.Black, e.ClipRectangle)
        If mode = simMode.smNull Then
            Dim font2 As Font
            font2 = New Font("Tahoma", 22)
            e.Graphics.DrawString(
                GameName + " Simulator",
                font2, Brushes.White,
                New Point(brd, picScatter.Height / 2)
                )
            Exit Sub
        End If
        If font1 Is Nothing Then
            font1 = New Font("Tahoma", 28)
        End If
        If font3 Is Nothing Then
            font3 = New Font("Tahoma", 8)
        End If

        Dim xinc As Integer, yinc As Integer
        xinc = (picScatter.Width - 2 * brd) / GetWidth()
        yinc = (picScatter.Height - 2 * brd) / GetHeight(2)
        Dim sz As Drawing.Size
        sz = New Drawing.Size(CLng(xinc * 0.95), CLng(yinc * 0.95))

        Dim p As Point = New Point(brd, brd)
        Dim base_point As Point = New Point(brd, brd * 2 / 3)

        Dim x As Long, y As Long
        For x = 1 To GetWidth()
            p = New Point(base_point)
            For y = 1 To GetHeight(x - 1)
                Dim tt As Long
                tt = GetScatterSymbol(y - 1, x - 1)
                If tt >= 0 Then
                    Dim brush1 As Brush
                    brush1 = New SolidBrush(Color.FromName(repertoir_type(tt)))
                    e.Graphics.DrawString(repertoir(tt), font1, brush1, p)
                    If GetCellTag(y - 1, x - 1) > 0 Then
                        e.Graphics.DrawLine(Pens.DarkOrange, p.X + 3, p.Y + yinc - 3, p.X + xinc - 20, p.Y + yinc - 3)
                    End If
                End If
                p.Offset(0, yinc)
            Next
            base_point.Offset(xinc, 0)
        Next

        If SelectedWinLine >= 0 Then
            If SelectedWinLineType = 1 Then
                base_point = New Point(brd, brd)
                For j = 0 To GetWinLineLen(SelectedWinLine) - 1
                    Dim rect As Rectangle

                    p = New Point(base_point)
                    p.Offset(0, GetWinLineWhere(SelectedWinLine, j) * yinc)
                    rect = New Rectangle(p, sz)
                    e.Graphics.DrawRectangle(Pens.Red, rect)
                    base_point.Offset(xinc, 0)
                Next j
            End If
        End If
    End Sub

    Private Sub lstWinLines_SelectedIndexChanged(sender As Object, e As EventArgs) Handles lstWinLines.SelectedIndexChanged
        If lstWinLines.SelectedIndex < 0 Then
            SelectedWinLine = lstWinLines.SelectedIndex
            SelectedWinLineType = -1
        Else
            If WinLinesType(lstWinLines.SelectedIndex) = 0 Then
                SelectedWinLine = lstWinLines.SelectedIndex
                SelectedWinLineType = -1
            ElseIf WinLinesType(lstWinLines.SelectedIndex) = 1 Then
                SelectedWinLine = WinLinesRef(lstWinLines.SelectedIndex)
                SelectedWinLineType = WinLinesType(lstWinLines.SelectedIndex)
            End If
        End If
        picScatter.Invalidate()
    End Sub

    Private Sub btnCreateLog_Click(sender As Object, e As EventArgs) Handles btnCreateLog.Click
        Dim LogFileName As New StringBuilder(100)
        LogFileName.Append(LogPrefix)
        BulkLog(LogFileName, LogFileName.Capacity, GameName_1, GameName_1.Capacity)
        lblThisIsFreeSpin.Text = LogFileName.ToString()
        lblThisIsFreeSpin.Visible = True
    End Sub

    Private Sub btnRereadSettings_Click(sender As Object, e As EventArgs) Handles btnRereadSettings.Click
        SimReload()
        LoadReelSymbols()
        LoadVisualParams()
        picScatter.Invalidate()
     End Sub

    Private Sub txtNumGames_GotFocus(sender As Object, e As EventArgs) Handles txtNumGames.GotFocus
        Me.AcceptButton = btBulk
    End Sub

    Private Sub txtNumGames_LostFocus(sender As Object, e As EventArgs) Handles txtNumGames.LostFocus
        Me.AcceptButton = btOne
    End Sub

    Private Sub Form1_GotFocus(sender As Object, e As EventArgs) Handles Me.GotFocus
        If flashing Then
            Dim fwi As New FLASHWINFO
            With fwi
                .hwnd = Me.Handle
                .dwFlags = 0
                .uCount = 0
                .cbSize = CUInt(System.Runtime.InteropServices.Marshal.SizeOf(fwi))
            End With

            FlashWindowEx(fwi)
            flashing = False
        End If
    End Sub
End Class
