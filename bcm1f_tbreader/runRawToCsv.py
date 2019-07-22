import glob
import os, sys


inputPath = "/localdata/TestBeamMay2019/bcm1f_2019"
outputPath = "/localdata/TestBeamMay2019_csv/zichen"

for inputFile in glob.glob(inputPath + "/run*.raw"): 
  runNumber  = inputFile[-10:-4]
  argv = "{} {} {}".format(inputFile,outputPath,runNumber)
  print(argv)
  os.system("bin/ubcmReader.exe " + argv)
  os.system("bin/VMEReader.exe " + argv)
