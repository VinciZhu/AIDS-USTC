Get-ChildItem .\rs\lab3\zips\*\*.txt |
ForEach-Object {
    $Pg = Get-Item $_.FullName.Replace('.txt', '.asm')
    # .\build\bin\lab3_disassembler.exe $_.FullName
    # .\build\bin\lab3_tester.exe $Pg.FullName
    # .\build\bin\lab3_decoder.exe $_.FullName
    $Out = Get-Content $_.FullName.Replace('.txt', '.out')
    $Props = @{
        LineCount   = 0
        InstCount   = "???"
        Correctness = "invalid"
        StudentID   = "PB????????"
    }
    if ($Out.Count -gt 1) {
        $Props.StudentID = $Out[-1] -replace 'student number: '
        $Props.LineCount = $Out[-2] -replace 'line count: '
        $Props.InstCount = $Out[-3] -replace 'average instruction count: '
        $Props.Correctness = $Out[-5] -replace 'correctness: '
    }
    else {
        $Props.StudentID = $Out -replace 'student number: '
        $Props.LineCount = (Get-Content $Pg.FullName).Count - 2
    }
    $Pg | Add-Member -NotePropertyMembers $Props -PassThru    
} |
Sort-Object -Property Correctness, LineCount, InstCount |
Format-Table -Property Name, StudentID, Correctness, LineCount, InstCount