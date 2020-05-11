#!/usr/bin/env python
"""
This is a small script that does the equivalent of multicrab.
"""
import os
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException


def getOptions():
    """
    Parse and return the arguments provided by the user.
    """
    usage = ("Usage: %prog --crabCmd CMD [--workArea WAD --crabCmdOpts OPTS]"
             "\nThe multicrab command executes 'crab CMD OPTS' for each project directory contained in WAD"
             "\nUse multicrab -h for help")

    parser = OptionParser(usage=usage)

    parser.add_option('-c', '--crabCmd',
                      dest = 'crabCmd',
                      default = '',
                      help = "crab command",
                      metavar = 'CMD')

    parser.add_option('-w', '--workArea',
                      dest = 'workArea',
                      default = '',
                      help = "work area directory (only if CMD != 'submit')",
                      metavar = 'WAD')

    parser.add_option('-o', '--crabCmdOpts',
                      dest = 'crabCmdOpts',
                      default = '',
                      help = "options for crab command CMD",
                      metavar = 'OPTS')

    (options, arguments) = parser.parse_args()

    if arguments:
        parser.error("Found positional argument(s): %s." % (arguments))
    if not options.crabCmd:
        parser.error("(-c CMD, --crabCmd=CMD) option not provided.")
    if options.crabCmd != 'submit':
        if not options.workArea:
            parser.error("(-w WAR, --workArea=WAR) option not provided.")
        if not os.path.isdir(options.workArea):
            parser.error("'%s' is not a valid directory." % (options.workArea))

    return options


def main():

    options = getOptions()

    # The submit command needs special treatment.
    if options.crabCmd == 'submit':

        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
        from CRABClient.UserUtilities import config, getUsernameFromSiteDB
        config = config()

        config.General.requestName = None
        config.General.workArea = '2017_SingleMuon_prod'
        config.General.transferOutputs = True
        config.General.transferLogs = False

        config.JobType.pluginName = 'Analysis'
        
	config.JobType.psetName = 'makingBacon_Data_25ns_MINIAOD.py'
        #config.JobType.pyCfgParams = []
        config.JobType.outputFiles = ['Output.root']

        config.Data.inputDataset = None
        config.Data.inputDBS = 'global'
        config.Data.ignoreLocality = True
        config.section_("Debug")
        config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']
        config.Site.whitelist = ["T2*","T1*"]
        config.Data.splitting = 'EventAwareLumiBased'
        #config.Data.splitting = 'LumiBased'
        config.Data.unitsPerJob = 50000 #78000
        # config.Data.totalUnits = 500000
        #config.Data.unitsPerJob = 1
        config.Data.outputDatasetTag = None
        #config.Data.outLFNDirBase = '/store/user/%s/ % (getUsernameFromSiteDB())
        config.Data.outLFNDirBase = '/store/user/zichen' #'/store/group/lpcbacon/jbueghly/'

        config.Site.storageSite = 'T3_US_FNALLPC' # Choose your site. 
        #--------------------------------------------------------

        # Will submit one task for each of these input datasets.
        inputDatasets = [
			'/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD',
			'/SingleMuon/Run2017C-31Mar2018-v1/MINIAOD',
			'/SingleMuon/Run2017D-31Mar2018-v1/MINIAOD',
			'/SingleMuon/Run2017E-31Mar2018-v1/MINIAOD',
			'/SingleMuon/Run2017F-31Mar2018-v1/MINIAOD'
                        ]

        for inDS in inputDatasets:
            config.General.requestName = inDS.split('/')[1] + '_' + inDS.split('/')[2] 
            config.Data.inputDataset = inDS
            config.Data.outputDatasetTag = '%s_%s' % (config.General.workArea, config.General.requestName)
            # Submit.
            try:
                print "Submitting for input dataset %s" % (inDS)
                crabCommand(options.crabCmd, config = config, *options.crabCmdOpts.split())
            except HTTPException as hte:
                print "Submission for input dataset %s failed: %s" % (inDS, hte.headers)
            except ClientException as cle:
                print "Submission for input dataset %s failed: %s" % (inDS, cle)

    # All other commands can be simply executed.
    elif options.workArea:

        for dir in os.listdir(options.workArea):
            projDir = os.path.join(options.workArea, dir)
            if not os.path.isdir(projDir):
                continue
            # Execute the crab command.
            msg = "Executing (the equivalent of): crab %s --dir %s %s" % (options.crabCmd, projDir, options.crabCmdOpts)
            print "-"*len(msg)
            print msg
            print "-"*len(msg)
            try:
                crabCommand(options.crabCmd, dir = projDir, *options.crabCmdOpts.split())
            except HTTPException as hte:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, hte.headers)
            except ClientException as cle:
                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, cle)


if __name__ == '__main__':
    main()
