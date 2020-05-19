export CVMFS_SL7_PATH=/cvmfs/cms-lpc.opensciencegrid.org/sl7

#Set the CUDA environment variables
echo "Setting the CUDA PATH and LD_LIBRARY_PATH environment variables..."
export CUDA_HOME=${CVMFS_SL7_PATH}/usr/local/cuda
if [ ! $PATH ]
then
        export PATH=$CUDA_HOME/bin
else
        export PATH=$CUDA_HOME/bin:$PATH
fi

if [ ! $LD_LIBRARY_PATH ]
then
        export LD_LIBRARY_PATH=$CUDA_HOME/extras/CUPTI/lib64:$CUDA_HOME/lib64
else
        export LD_LIBRARY_PATH=$CUDA_HOME/extras/CUPTI/lib64:$CUDA_HOME/lib64:$LD_LIBRARY_PATH
fi


alias initlab='jupyter lab --no-browser --port=8080'
export PYTHONPATH=$PYTHONPATH:/uscms/home/zchen/nobackup/NanoBLT/NanoBLT_OpenCL

# added by Anaconda3 2019.10 installer
# >>> conda init >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$(CONDA_REPORT_ERRORS=false '/uscms/home/zchen/nobackup/anaconda/bin/conda' shell.bash hook 2> /dev/null)"
if [ $? -eq 0 ]; then
    \eval "$__conda_setup"
else
    if [ -f "/uscms/home/zchen/nobackup/anaconda/etc/profile.d/conda.sh" ]; then
        . "/uscms/home/zchen/nobackup/anaconda/etc/profile.d/conda.sh"
        CONDA_CHANGEPS1=false conda activate base
    else
        \export PATH="/uscms/home/zchen/nobackup/anaconda/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda init <<<
