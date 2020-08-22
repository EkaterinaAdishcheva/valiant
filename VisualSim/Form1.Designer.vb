<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.btOk = New System.Windows.Forms.Button()
        Me.btBulk = New System.Windows.Forms.Button()
        Me.btOne = New System.Windows.Forms.Button()
        Me.txtNumGames = New System.Windows.Forms.TextBox()
        Me.picScatter = New System.Windows.Forms.PictureBox()
        Me.prBulk = New System.Windows.Forms.ProgressBar()
        Me.btnReset = New System.Windows.Forms.Button()
        Me.gbOneGame1 = New System.Windows.Forms.GroupBox()
        Me.txtBalance = New System.Windows.Forms.TextBox()
        Me.txtThisWin = New System.Windows.Forms.TextBox()
        Me.lstWinLines = New System.Windows.Forms.ListBox()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.lblThisWin = New System.Windows.Forms.Label()
        Me.lblWinLines = New System.Windows.Forms.Label()
        Me.btnCreateLog = New System.Windows.Forms.Button()
        Me.gbOneGame2 = New System.Windows.Forms.GroupBox()
        Me.lblWaitWin = New System.Windows.Forms.Label()
        Me.txtWaitWin = New System.Windows.Forms.TextBox()
        Me.checkBonus4 = New System.Windows.Forms.CheckBox()
        Me.checkBonus3 = New System.Windows.Forms.CheckBox()
        Me.checkBonus2 = New System.Windows.Forms.CheckBox()
        Me.checkBonus1 = New System.Windows.Forms.CheckBox()
        Me.txtTotalWin = New System.Windows.Forms.TextBox()
        Me.txtTotalSpins = New System.Windows.Forms.TextBox()
        Me.txtRTP = New System.Windows.Forms.TextBox()
        Me.txtFreeWin = New System.Windows.Forms.TextBox()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.lblRTP = New System.Windows.Forms.Label()
        Me.lblTotalWin = New System.Windows.Forms.Label()
        Me.lblTotalGames = New System.Windows.Forms.Label()
        Me.lblThisIsFreeSpin = New System.Windows.Forms.Label()
        Me.txtStartBalance = New System.Windows.Forms.TextBox()
        Me.lblNumGames = New System.Windows.Forms.Label()
        Me.lblStartingBalance = New System.Windows.Forms.Label()
        Me.txtBet = New System.Windows.Forms.TextBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.btnRereadSettings = New System.Windows.Forms.Button()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.txtBulkWin = New System.Windows.Forms.TextBox()
        Me.txtBulkGames = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.lblLogFileName = New System.Windows.Forms.Label()
        Me.txtBulkRTP = New System.Windows.Forms.TextBox()
        Me.lblSaved = New System.Windows.Forms.Label()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.txtBulkHitRate = New System.Windows.Forms.TextBox()
        Me.gbBulk = New System.Windows.Forms.GroupBox()
        Me.txtProgress = New System.Windows.Forms.TextBox()
        Me.txtTechInfo = New System.Windows.Forms.TextBox()
        CType(Me.picScatter, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.gbOneGame1.SuspendLayout()
        Me.gbOneGame2.SuspendLayout()
        Me.gbBulk.SuspendLayout()
        Me.SuspendLayout()
        '
        'btOk
        '
        Me.btOk.Location = New System.Drawing.Point(698, 284)
        Me.btOk.Name = "btOk"
        Me.btOk.Size = New System.Drawing.Size(75, 23)
        Me.btOk.TabIndex = 45
        Me.btOk.Text = "OK"
        Me.btOk.UseVisualStyleBackColor = True
        '
        'btBulk
        '
        Me.btBulk.Location = New System.Drawing.Point(304, 284)
        Me.btBulk.Name = "btBulk"
        Me.btBulk.Size = New System.Drawing.Size(75, 23)
        Me.btBulk.TabIndex = 33
        Me.btBulk.Text = "Bulk run"
        Me.btBulk.UseVisualStyleBackColor = True
        '
        'btOne
        '
        Me.btOne.Location = New System.Drawing.Point(526, 284)
        Me.btOne.Name = "btOne"
        Me.btOne.Size = New System.Drawing.Size(75, 23)
        Me.btOne.TabIndex = 1
        Me.btOne.Text = "One Spin"
        Me.btOne.UseVisualStyleBackColor = True
        '
        'txtNumGames
        '
        Me.txtNumGames.Location = New System.Drawing.Point(179, 285)
        Me.txtNumGames.Name = "txtNumGames"
        Me.txtNumGames.Size = New System.Drawing.Size(119, 20)
        Me.txtNumGames.TabIndex = 31
        Me.txtNumGames.Text = "500000"
        Me.txtNumGames.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'picScatter
        '
        Me.picScatter.Location = New System.Drawing.Point(199, 12)
        Me.picScatter.Name = "picScatter"
        Me.picScatter.Size = New System.Drawing.Size(381, 225)
        Me.picScatter.TabIndex = 2
        Me.picScatter.TabStop = False
        '
        'prBulk
        '
        Me.prBulk.Location = New System.Drawing.Point(103, 214)
        Me.prBulk.Name = "prBulk"
        Me.prBulk.Size = New System.Drawing.Size(612, 23)
        Me.prBulk.TabIndex = 3
        Me.prBulk.Visible = False
        '
        'btnReset
        '
        Me.btnReset.Enabled = False
        Me.btnReset.Location = New System.Drawing.Point(613, 284)
        Me.btnReset.Name = "btnReset"
        Me.btnReset.Size = New System.Drawing.Size(75, 23)
        Me.btnReset.TabIndex = 44
        Me.btnReset.Text = "Reset"
        Me.btnReset.UseVisualStyleBackColor = True
        '
        'gbOneGame1
        '
        Me.gbOneGame1.Controls.Add(Me.txtBalance)
        Me.gbOneGame1.Controls.Add(Me.txtThisWin)
        Me.gbOneGame1.Controls.Add(Me.lstWinLines)
        Me.gbOneGame1.Controls.Add(Me.Label6)
        Me.gbOneGame1.Controls.Add(Me.lblThisWin)
        Me.gbOneGame1.Controls.Add(Me.lblWinLines)
        Me.gbOneGame1.Controls.Add(Me.btnCreateLog)
        Me.gbOneGame1.Location = New System.Drawing.Point(12, 12)
        Me.gbOneGame1.Name = "gbOneGame1"
        Me.gbOneGame1.Size = New System.Drawing.Size(172, 250)
        Me.gbOneGame1.TabIndex = 5
        Me.gbOneGame1.TabStop = False
        Me.gbOneGame1.Visible = False
        '
        'txtBalance
        '
        Me.txtBalance.Location = New System.Drawing.Point(6, 131)
        Me.txtBalance.Name = "txtBalance"
        Me.txtBalance.ReadOnly = True
        Me.txtBalance.Size = New System.Drawing.Size(157, 20)
        Me.txtBalance.TabIndex = 22
        '
        'txtThisWin
        '
        Me.txtThisWin.Location = New System.Drawing.Point(6, 168)
        Me.txtThisWin.Name = "txtThisWin"
        Me.txtThisWin.ReadOnly = True
        Me.txtThisWin.Size = New System.Drawing.Size(157, 20)
        Me.txtThisWin.TabIndex = 23
        '
        'lstWinLines
        '
        Me.lstWinLines.FormattingEnabled = True
        Me.lstWinLines.Location = New System.Drawing.Point(6, 32)
        Me.lstWinLines.Name = "lstWinLines"
        Me.lstWinLines.Size = New System.Drawing.Size(157, 82)
        Me.lstWinLines.TabIndex = 21
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(6, 118)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(83, 13)
        Me.Label6.TabIndex = 0
        Me.Label6.Text = "Current Balance"
        '
        'lblThisWin
        '
        Me.lblThisWin.AutoSize = True
        Me.lblThisWin.Location = New System.Drawing.Point(6, 155)
        Me.lblThisWin.Name = "lblThisWin"
        Me.lblThisWin.Size = New System.Drawing.Size(68, 13)
        Me.lblThisWin.TabIndex = 0
        Me.lblThisWin.Text = "This spin win"
        '
        'lblWinLines
        '
        Me.lblWinLines.AutoSize = True
        Me.lblWinLines.Location = New System.Drawing.Point(6, 16)
        Me.lblWinLines.Name = "lblWinLines"
        Me.lblWinLines.Size = New System.Drawing.Size(74, 13)
        Me.lblWinLines.TabIndex = 0
        Me.lblWinLines.Text = "Winning Lines"
        '
        'btnCreateLog
        '
        Me.btnCreateLog.Location = New System.Drawing.Point(5, 218)
        Me.btnCreateLog.Name = "btnCreateLog"
        Me.btnCreateLog.Size = New System.Drawing.Size(75, 23)
        Me.btnCreateLog.TabIndex = 20
        Me.btnCreateLog.Text = "Write Log File"
        Me.btnCreateLog.UseVisualStyleBackColor = True
        '
        'gbOneGame2
        '
        Me.gbOneGame2.Controls.Add(Me.lblWaitWin)
        Me.gbOneGame2.Controls.Add(Me.txtWaitWin)
        Me.gbOneGame2.Controls.Add(Me.checkBonus4)
        Me.gbOneGame2.Controls.Add(Me.checkBonus3)
        Me.gbOneGame2.Controls.Add(Me.checkBonus2)
        Me.gbOneGame2.Controls.Add(Me.checkBonus1)
        Me.gbOneGame2.Controls.Add(Me.txtTotalWin)
        Me.gbOneGame2.Controls.Add(Me.txtTotalSpins)
        Me.gbOneGame2.Controls.Add(Me.txtRTP)
        Me.gbOneGame2.Controls.Add(Me.txtFreeWin)
        Me.gbOneGame2.Controls.Add(Me.Label8)
        Me.gbOneGame2.Controls.Add(Me.lblRTP)
        Me.gbOneGame2.Controls.Add(Me.lblTotalWin)
        Me.gbOneGame2.Controls.Add(Me.lblTotalGames)
        Me.gbOneGame2.Location = New System.Drawing.Point(601, 12)
        Me.gbOneGame2.Name = "gbOneGame2"
        Me.gbOneGame2.Size = New System.Drawing.Size(172, 250)
        Me.gbOneGame2.TabIndex = 4
        Me.gbOneGame2.TabStop = False
        Me.gbOneGame2.Visible = False
        '
        'lblWaitWin
        '
        Me.lblWaitWin.AutoSize = True
        Me.lblWaitWin.Location = New System.Drawing.Point(9, 228)
        Me.lblWaitWin.Name = "lblWaitWin"
        Me.lblWaitWin.Size = New System.Drawing.Size(81, 13)
        Me.lblWaitWin.TabIndex = 8
        Me.lblWaitWin.Text = "Wait win above"
        '
        'txtWaitWin
        '
        Me.txtWaitWin.Location = New System.Drawing.Point(97, 224)
        Me.txtWaitWin.Name = "txtWaitWin"
        Me.txtWaitWin.Size = New System.Drawing.Size(66, 20)
        Me.txtWaitWin.TabIndex = 10
        '
        'checkBonus4
        '
        Me.checkBonus4.AutoSize = True
        Me.checkBonus4.Location = New System.Drawing.Point(7, 206)
        Me.checkBonus4.Name = "checkBonus4"
        Me.checkBonus4.Size = New System.Drawing.Size(105, 17)
        Me.checkBonus4.TabIndex = 14
        Me.checkBonus4.Text = "Wait for Bonus 4"
        Me.checkBonus4.UseVisualStyleBackColor = True
        Me.checkBonus4.Visible = False
        '
        'checkBonus3
        '
        Me.checkBonus3.AutoSize = True
        Me.checkBonus3.Location = New System.Drawing.Point(7, 190)
        Me.checkBonus3.Name = "checkBonus3"
        Me.checkBonus3.Size = New System.Drawing.Size(105, 17)
        Me.checkBonus3.TabIndex = 13
        Me.checkBonus3.Text = "Wait for Bonus 3"
        Me.checkBonus3.UseVisualStyleBackColor = True
        Me.checkBonus3.Visible = False
        '
        'checkBonus2
        '
        Me.checkBonus2.AutoSize = True
        Me.checkBonus2.Location = New System.Drawing.Point(7, 174)
        Me.checkBonus2.Name = "checkBonus2"
        Me.checkBonus2.Size = New System.Drawing.Size(105, 17)
        Me.checkBonus2.TabIndex = 12
        Me.checkBonus2.Text = "Wait for Bonus 2"
        Me.checkBonus2.UseVisualStyleBackColor = True
        '
        'checkBonus1
        '
        Me.checkBonus1.AutoSize = True
        Me.checkBonus1.Location = New System.Drawing.Point(7, 157)
        Me.checkBonus1.Name = "checkBonus1"
        Me.checkBonus1.Size = New System.Drawing.Size(105, 17)
        Me.checkBonus1.TabIndex = 11
        Me.checkBonus1.Text = "Wait for Bonus 1"
        Me.checkBonus1.UseVisualStyleBackColor = True
        '
        'txtTotalWin
        '
        Me.txtTotalWin.Location = New System.Drawing.Point(6, 62)
        Me.txtTotalWin.Name = "txtTotalWin"
        Me.txtTotalWin.ReadOnly = True
        Me.txtTotalWin.Size = New System.Drawing.Size(157, 20)
        Me.txtTotalWin.TabIndex = 25
        '
        'txtTotalSpins
        '
        Me.txtTotalSpins.Location = New System.Drawing.Point(6, 26)
        Me.txtTotalSpins.Name = "txtTotalSpins"
        Me.txtTotalSpins.ReadOnly = True
        Me.txtTotalSpins.Size = New System.Drawing.Size(157, 20)
        Me.txtTotalSpins.TabIndex = 24
        '
        'txtRTP
        '
        Me.txtRTP.Location = New System.Drawing.Point(6, 131)
        Me.txtRTP.Name = "txtRTP"
        Me.txtRTP.ReadOnly = True
        Me.txtRTP.Size = New System.Drawing.Size(157, 20)
        Me.txtRTP.TabIndex = 27
        '
        'txtFreeWin
        '
        Me.txtFreeWin.Location = New System.Drawing.Point(6, 98)
        Me.txtFreeWin.Name = "txtFreeWin"
        Me.txtFreeWin.ReadOnly = True
        Me.txtFreeWin.Size = New System.Drawing.Size(157, 20)
        Me.txtFreeWin.TabIndex = 26
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(6, 118)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(66, 13)
        Me.Label8.TabIndex = 0
        Me.Label8.Text = "Current RTP"
        '
        'lblRTP
        '
        Me.lblRTP.AutoSize = True
        Me.lblRTP.Location = New System.Drawing.Point(6, 85)
        Me.lblRTP.Name = "lblRTP"
        Me.lblRTP.Size = New System.Drawing.Size(74, 13)
        Me.lblRTP.TabIndex = 0
        Me.lblRTP.Text = "Free Spin Win"
        '
        'lblTotalWin
        '
        Me.lblTotalWin.AutoSize = True
        Me.lblTotalWin.Location = New System.Drawing.Point(6, 49)
        Me.lblTotalWin.Name = "lblTotalWin"
        Me.lblTotalWin.Size = New System.Drawing.Size(53, 13)
        Me.lblTotalWin.TabIndex = 0
        Me.lblTotalWin.Text = "Total Win"
        '
        'lblTotalGames
        '
        Me.lblTotalGames.AutoSize = True
        Me.lblTotalGames.Location = New System.Drawing.Point(6, 13)
        Me.lblTotalGames.Name = "lblTotalGames"
        Me.lblTotalGames.Size = New System.Drawing.Size(60, 13)
        Me.lblTotalGames.TabIndex = 0
        Me.lblTotalGames.Text = "Total Spins"
        '
        'lblThisIsFreeSpin
        '
        Me.lblThisIsFreeSpin.AutoSize = True
        Me.lblThisIsFreeSpin.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(204, Byte))
        Me.lblThisIsFreeSpin.ForeColor = System.Drawing.Color.FromArgb(CType(CType(192, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer))
        Me.lblThisIsFreeSpin.Location = New System.Drawing.Point(197, 249)
        Me.lblThisIsFreeSpin.Name = "lblThisIsFreeSpin"
        Me.lblThisIsFreeSpin.Size = New System.Drawing.Size(86, 13)
        Me.lblThisIsFreeSpin.TabIndex = 0
        Me.lblThisIsFreeSpin.Text = "Spin Message"
        Me.lblThisIsFreeSpin.Visible = False
        '
        'txtStartBalance
        '
        Me.txtStartBalance.Location = New System.Drawing.Point(401, 285)
        Me.txtStartBalance.Name = "txtStartBalance"
        Me.txtStartBalance.Size = New System.Drawing.Size(119, 20)
        Me.txtStartBalance.TabIndex = 34
        Me.txtStartBalance.Text = "100000"
        Me.txtStartBalance.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'lblNumGames
        '
        Me.lblNumGames.AutoSize = True
        Me.lblNumGames.Location = New System.Drawing.Point(176, 269)
        Me.lblNumGames.Name = "lblNumGames"
        Me.lblNumGames.Size = New System.Drawing.Size(83, 13)
        Me.lblNumGames.TabIndex = 3
        Me.lblNumGames.Text = "Games in a bulk"
        '
        'lblStartingBalance
        '
        Me.lblStartingBalance.AutoSize = True
        Me.lblStartingBalance.Location = New System.Drawing.Point(398, 269)
        Me.lblStartingBalance.Name = "lblStartingBalance"
        Me.lblStartingBalance.Size = New System.Drawing.Size(85, 13)
        Me.lblStartingBalance.TabIndex = 3
        Me.lblStartingBalance.Text = "Starting Balance"
        '
        'txtBet
        '
        Me.txtBet.Location = New System.Drawing.Point(18, 284)
        Me.txtBet.Name = "txtBet"
        Me.txtBet.Size = New System.Drawing.Size(119, 20)
        Me.txtBet.TabIndex = 35
        Me.txtBet.Text = "1"
        Me.txtBet.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(18, 266)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(23, 13)
        Me.Label7.TabIndex = 3
        Me.Label7.Text = "Bet"
        '
        'btnRereadSettings
        '
        Me.btnRereadSettings.Location = New System.Drawing.Point(600, 50)
        Me.btnRereadSettings.Name = "btnRereadSettings"
        Me.btnRereadSettings.Size = New System.Drawing.Size(150, 23)
        Me.btnRereadSettings.TabIndex = 39
        Me.btnRereadSettings.Text = "Reread Settings"
        Me.btnRereadSettings.UseVisualStyleBackColor = True
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(9, 51)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(50, 13)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "Total win"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(9, 106)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(66, 13)
        Me.Label5.TabIndex = 3
        Me.Label5.Text = "Current RTP"
        '
        'txtBulkWin
        '
        Me.txtBulkWin.Location = New System.Drawing.Point(87, 48)
        Me.txtBulkWin.Name = "txtBulkWin"
        Me.txtBulkWin.ReadOnly = True
        Me.txtBulkWin.Size = New System.Drawing.Size(100, 20)
        Me.txtBulkWin.TabIndex = 4
        '
        'txtBulkGames
        '
        Me.txtBulkGames.Location = New System.Drawing.Point(87, 27)
        Me.txtBulkGames.Name = "txtBulkGames"
        Me.txtBulkGames.ReadOnly = True
        Me.txtBulkGames.Size = New System.Drawing.Size(100, 20)
        Me.txtBulkGames.TabIndex = 4
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(9, 30)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(65, 13)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Total games"
        '
        'lblLogFileName
        '
        Me.lblLogFileName.AutoSize = True
        Me.lblLogFileName.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(204, Byte))
        Me.lblLogFileName.ForeColor = System.Drawing.Color.FromArgb(CType(CType(192, Byte), Integer), CType(CType(0, Byte), Integer), CType(CType(0, Byte), Integer))
        Me.lblLogFileName.Location = New System.Drawing.Point(72, 197)
        Me.lblLogFileName.Name = "lblLogFileName"
        Me.lblLogFileName.Size = New System.Drawing.Size(88, 13)
        Me.lblLogFileName.TabIndex = 0
        Me.lblLogFileName.Text = "Log File Name"
        '
        'txtBulkRTP
        '
        Me.txtBulkRTP.Location = New System.Drawing.Point(87, 103)
        Me.txtBulkRTP.Name = "txtBulkRTP"
        Me.txtBulkRTP.ReadOnly = True
        Me.txtBulkRTP.Size = New System.Drawing.Size(100, 20)
        Me.txtBulkRTP.TabIndex = 4
        '
        'lblSaved
        '
        Me.lblSaved.AutoSize = True
        Me.lblSaved.Location = New System.Drawing.Point(219, 15)
        Me.lblSaved.Name = "lblSaved"
        Me.lblSaved.Size = New System.Drawing.Size(48, 13)
        Me.lblSaved.TabIndex = 5
        Me.lblSaved.Text = "lblSaved"
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(8, 125)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(46, 13)
        Me.Label9.TabIndex = 6
        Me.Label9.Text = "Hit Rate"
        '
        'txtBulkHitRate
        '
        Me.txtBulkHitRate.Location = New System.Drawing.Point(87, 125)
        Me.txtBulkHitRate.Name = "txtBulkHitRate"
        Me.txtBulkHitRate.ReadOnly = True
        Me.txtBulkHitRate.Size = New System.Drawing.Size(100, 20)
        Me.txtBulkHitRate.TabIndex = 7
        '
        'gbBulk
        '
        Me.gbBulk.Controls.Add(Me.txtBulkHitRate)
        Me.gbBulk.Controls.Add(Me.Label9)
        Me.gbBulk.Controls.Add(Me.lblSaved)
        Me.gbBulk.Controls.Add(Me.txtBulkRTP)
        Me.gbBulk.Controls.Add(Me.lblLogFileName)
        Me.gbBulk.Controls.Add(Me.Label1)
        Me.gbBulk.Controls.Add(Me.txtBulkGames)
        Me.gbBulk.Controls.Add(Me.txtBulkWin)
        Me.gbBulk.Controls.Add(Me.Label5)
        Me.gbBulk.Controls.Add(Me.Label2)
        Me.gbBulk.Location = New System.Drawing.Point(20, 17)
        Me.gbBulk.Name = "gbBulk"
        Me.gbBulk.Size = New System.Drawing.Size(593, 220)
        Me.gbBulk.TabIndex = 6
        Me.gbBulk.TabStop = False
        Me.gbBulk.Visible = False
        '
        'txtProgress
        '
        Me.txtProgress.Cursor = System.Windows.Forms.Cursors.Arrow
        Me.txtProgress.Enabled = False
        Me.txtProgress.Location = New System.Drawing.Point(450, 40)
        Me.txtProgress.Name = "txtProgress"
        Me.txtProgress.ReadOnly = True
        Me.txtProgress.Size = New System.Drawing.Size(200, 20)
        Me.txtProgress.TabIndex = 31
        Me.txtProgress.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        Me.txtProgress.Visible = False
        '
        'txtTechInfo
        '
        Me.txtTechInfo.Cursor = System.Windows.Forms.Cursors.Arrow
        Me.txtTechInfo.Enabled = False
        Me.txtTechInfo.Location = New System.Drawing.Point(450, 100)
        Me.txtTechInfo.Name = "txtTechInfo"
        Me.txtTechInfo.ReadOnly = True
        Me.txtTechInfo.Size = New System.Drawing.Size(200, 20)
        Me.txtTechInfo.TabIndex = 46
        Me.txtTechInfo.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        Me.txtTechInfo.Visible = False
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(785, 317)
        Me.Controls.Add(Me.txtTechInfo)
        Me.Controls.Add(Me.btnRereadSettings)
        Me.Controls.Add(Me.gbBulk)
        Me.Controls.Add(Me.gbOneGame2)
        Me.Controls.Add(Me.gbOneGame1)
        Me.Controls.Add(Me.lblThisIsFreeSpin)
        Me.Controls.Add(Me.prBulk)
        Me.Controls.Add(Me.txtStartBalance)
        Me.Controls.Add(Me.lblStartingBalance)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.lblNumGames)
        Me.Controls.Add(Me.txtProgress)
        Me.Controls.Add(Me.txtBet)
        Me.Controls.Add(Me.txtNumGames)
        Me.Controls.Add(Me.btnReset)
        Me.Controls.Add(Me.btOne)
        Me.Controls.Add(Me.btBulk)
        Me.Controls.Add(Me.btOk)
        Me.Controls.Add(Me.picScatter)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Name = "Form1"
        Me.Text = "Slot Simulator"
        CType(Me.picScatter, System.ComponentModel.ISupportInitialize).EndInit()
        Me.gbOneGame1.ResumeLayout(False)
        Me.gbOneGame1.PerformLayout()
        Me.gbOneGame2.ResumeLayout(False)
        Me.gbOneGame2.PerformLayout()
        Me.gbBulk.ResumeLayout(False)
        Me.gbBulk.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents btOk As Button
    Friend WithEvents btBulk As Button
    Friend WithEvents btOne As Button
    Friend WithEvents txtNumGames As TextBox
    Friend WithEvents picScatter As PictureBox
    Friend WithEvents prBulk As ProgressBar
    Friend WithEvents btnReset As Button
    Friend WithEvents gbOneGame1 As GroupBox
    Friend WithEvents lblWinLines As Label
    Friend WithEvents lstWinLines As ListBox
    Friend WithEvents txtThisWin As TextBox
    Friend WithEvents lblThisWin As Label
    Friend WithEvents gbOneGame2 As GroupBox
    Friend WithEvents txtTotalWin As TextBox
    Friend WithEvents txtTotalSpins As TextBox
    Friend WithEvents txtFreeWin As TextBox
    Friend WithEvents lblRTP As Label
    Friend WithEvents lblTotalWin As Label
    Friend WithEvents lblTotalGames As Label
    Friend WithEvents lblThisIsFreeSpin As Label
    Friend WithEvents txtStartBalance As TextBox
    Friend WithEvents lblNumGames As Label
    Friend WithEvents lblStartingBalance As Label
    Friend WithEvents txtBalance As TextBox
    Friend WithEvents Label6 As Label
    Friend WithEvents checkBonus4 As CheckBox
    Friend WithEvents checkBonus3 As CheckBox
    Friend WithEvents checkBonus2 As CheckBox
    Friend WithEvents checkBonus1 As CheckBox
    Friend WithEvents txtBet As TextBox
    Friend WithEvents Label7 As Label
    Friend WithEvents txtRTP As TextBox
    Friend WithEvents Label8 As Label
    Friend WithEvents txtWaitWin As TextBox
    Friend WithEvents lblWaitWin As Label
    Friend WithEvents btnCreateLog As Button
    Friend WithEvents btnRereadSettings As Button
    Friend WithEvents Label2 As Label
    Friend WithEvents Label5 As Label
    Friend WithEvents txtBulkWin As TextBox
    Friend WithEvents txtBulkGames As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents lblLogFileName As Label
    Friend WithEvents txtBulkRTP As TextBox
    Friend WithEvents lblSaved As Label
    Friend WithEvents Label9 As Label
    Friend WithEvents txtBulkHitRate As TextBox
    Friend WithEvents gbBulk As GroupBox
    Friend WithEvents txtProgress As TextBox
    Friend WithEvents txtTechInfo As TextBox
End Class
