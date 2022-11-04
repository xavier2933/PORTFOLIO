function Replace-Word {
    param($File_Path,$FindText,$ReplaceText)
    Write-Output $Findtext
    $Word = New-Object -ComObject Word.Application
    $WordFiles = Get-ChildItem -Path $File_Path -Recurse | ? Name -like "*.do[c,t]*"

    # $FindText = Read-Host -Prompt 'Word to replace' # <= Find this text
    # $ReplaceText = Read-Host -Prompt 'Replacement Word' # <= Replace it with this text

    $MatchCase = $false
    $MatchWholeWorld = $true
    $MatchWildcards = $false
    $MatchSoundsLike = $false
    $MatchAllWordForms = $false
    $Forward = $false
    $Wrap = 1
    $Format = $false
    $Replace = 2

    foreach($WordFile in $WordFiles) {
        # Open the document
        $Document = $Word.Documents.Open($WordFile.FullName)
        
        # Find and replace the text using the variables we just setup
        $Document.Content.Find.Execute($FindText, $MatchCase, $MatchWholeWorld, $MatchWildcards, $MatchSoundsLike, $MatchAllWordForms, $Forward, $Wrap, $Format, $ReplaceText, $Replace)
        
        # Save and close the document
        $Document.Close(-1) # The -1 corresponds to https://docs.microsoft.com/en-us/office/vba/api/word.wdsaveoptions
    }

    $Word.Quit()
}



Set-StrictMode -Version 3

## Load the Windows Forms assembly
Add-Type -Assembly System.Windows.Forms
## Create the main form

$form = New-Object Windows.Forms.Form
$form.Size = New-Object Drawing.Size @(400,200)
$form.FormBorderStyle = "FixedToolWindow"


## Create the listbox to hold the items from the pipeline

$textbox = New-Object Windows.Forms.TextBox
$textbox.Top = 5
$textbox.Left = 5
$textBox.Width = 380
$textbox.Anchor = "Left","Right"
$textBox.Text = 'Use the button to select folder'
$form.Text = 'Find Replace'

$textbox2 = New-Object Windows.Forms.TextBox
$textbox2.Top = 40
$textbox2.Left = 5
$textBox2.Width = 100
$textbox2.Text = "Word to replace"
$textbox2.Anchor = "Left","Right"


$textbox3 = New-Object Windows.Forms.TextBox
$textbox3.Top = 75
$textbox3.Left = 5
$textBox3.Width = 100
$textbox3.Text = "Replacement Word"
$textbox3.Anchor = "Left","Right"




## Create the button panel to hold the OK and Cancel buttons

$buttonPanel = New-Object Windows.Forms.Panel
$buttonPanel.Size = New-Object Drawing.Size @(400,40)
$buttonPanel.Dock = "Bottom"

$selectButton = New-Object Windows.Forms.Button
$selectButton.Text = 'Select'
$selectButton.Top = $buttonPanel.Height - $selectButton.Height - 10
$selectButton.Left = 20
$selectButton.Anchor = "Right"
$folderBrowser = New-Object System.Windows.Forms.folderBrowserDialog
$selectButton.Add_Click({
    $folderBrowser.ShowDialog()
    $textBox.Text = $folderBrowser.SelectedPath
})
$textBox.ReadOnly = $true

## Create the Cancel button, which will anchor to the bottom right
$cancelButton = New-Object Windows.Forms.Button
$cancelButton.Text = "Cancel"
$cancelButton.DialogResult = "Cancel"
$cancelButton.Top = $buttonPanel.Height - $cancelButton.Height - 10
$cancelButton.Left = $buttonPanel.Width - $cancelButton.Width - 10
$cancelButton.Anchor = "Right"


## Create the OK button, which will anchor to the left of Cancel
$okButton = New-Object Windows.Forms.Button
$okButton.Text = "Ok"
$okButton.DialogResult = "Ok"
$okButton.Top = $cancelButton.Top
$okButton.Left = $cancelButton.Left - $okButton.Width - 5
$okButton.Anchor = "Right"

## Add the buttons to the button panel
$buttonPanel.Controls.Add($okButton)
$buttonPanel.Controls.Add($cancelButton)
$buttonPanel.Controls.Add($selectButton)
## Add the button panel and list box to the form, and also set

## the actions for the buttons

$form.Controls.Add($buttonPanel)
$form.Controls.Add($textbox)
$form.Controls.Add($textbox2)
$form.Controls.Add($textbox3)
$form.AcceptButton = $okButton
$form.CancelButton = $cancelButton




$form.Add_Shown( { $form.Activate(); $textbox.Focus() } )


## Show the form, and wait for the response

$result = $form.ShowDialog()


## If they pressed OK (or Enter,) go through all the

## checked items and send the corresponding object down the pipeline

if($result -eq "OK")

{
    $textbox.Text
    $textbox2.Text
    $textbox3.Text
    Replace-Word $textbox.Text $textbox2.Text $textbox3.Text
}