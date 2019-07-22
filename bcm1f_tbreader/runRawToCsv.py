import glob
import os, sys


inputPath = "/localdata/TestBeamMay2019/bcm1f_2019"
outputPath = "/localdata/TestBeamMay2019_csv/zichen"

runs = ["223","216","217","218","219","198","220","221","222",
        "225","226","228","229","230","231","237","238","239","240","241"
        ]



for run in runs: 
  runNumber = "000" + run
  inputFile = inputPath + "/run{}.raw".format(runNumber)
  argv = "{} {} {}".format(inputFile,outputPath,runNumber)
  print(argv)
  os.system("bin/ubcmReader.exe " + argv)
  os.system("bin/VMEReader.exe " + argv)


# for inputFile in glob.glob(inputPath + "/run*.raw"): 
#   runNumber  = inputFile[-10:-4]
#   argv = "{} {} {}".format(inputFile,outputPath,runNumber)
#   print(argv)
#   os.system("bin/ubcmReader.exe " + argv)
#   os.system("bin/VMEReader.exe " + argv)
