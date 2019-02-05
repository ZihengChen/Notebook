################
# 1. ssh 
################
alias fnal='kinit zchen@FNAL.GOV'
alias sshlpc='ssh -X -Y -R 52691:127.0.0.1:52691 zchen@cmslpc-sl6.fnal.gov'
alias sshlxplus='ssh -X -Y -R 52698:127.0.0.1:52698 zichen@lxplus043.cern.ch'
alias sshws='ssh -Y -R 52698:127.0.0.1:52698 zchen@bahamut.phys.northwestern.edu'
alias juws='ssh -N -f -L localhost:8889:localhost:8889 zchen@bahamut.phys.northwestern.edu'


################
# 2. alias
################
alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'
alias mkdir='mkdir -p'
alias la='ls -A'
alias ll='ls -lh'
alias ju="jupyter notebook"


################
# 3. functions
################

# scp
tows(){ 
    scp $1 zchen@bahamut.phys.northwestern.edu:/home/zchen/$2
}

fromws(){
    scp zchen@bahamut.phys.northwestern.edu:/home/zchen/$1 $2
}

tolpc(){
    scp $1 zchen@cmslpc-sl6.fnal.gov:$2
}
fromlpc(){
    scp zchen@cmslpc-sl6.fnal.gov:$1 $2
}

# CMS tdr
an(){
eval `/Users/zihengchen/Documents/Analysis/docs/notes/tdr runtime -sh`
tdr  --draft --style=an b AN-18-030
}

pp(){
eval `/Users/zihengchen/Documents/Analysis/docs/papers/tdr runtime -sh`
tdr  --draft --style=paper b SMP-18-011
}


################
# 4. add path
################
# add python path
export PYTHONPATH=$PYTHONPATH:/Users/zihengchen/Documents/Analysis/workplace/scripts
export PYTHONPATH=$PYTHONPATH:/Users/zihengchen/Documents/AttoePIE/scripts
export PYTHONPATH=$PYTHONPATH:/Users/zihengchen/Documents/HGCal/scripts
export PYTHONPATH=$PYTHONPATH:/Users/zihengchen/Documents/ImageAlgorithm/ImageAlgoKD

# add root
export ROOTSYS=/usr/local/root
#export LD_LIBRARY_PATH=$ROOTSYS/lib:$PYTHONDIR/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH:$ROOTSYS/lib
source $ROOTSYS/bin/thisroot.sh


# added by Anaconda3 2018.12 installer
# >>> conda init >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$(CONDA_REPORT_ERRORS=false '/Users/zihengchen/anaconda3/bin/conda' shell.bash hook 2> /dev/null)"
if [ $? -eq 0 ]; then
    \eval "$__conda_setup"
else
    if [ -f "/Users/zihengchen/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/Users/zihengchen/anaconda3/etc/profile.d/conda.sh"
        CONDA_CHANGEPS1=false conda activate base
    else
        \export PATH="/Users/zihengchen/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda init <<<

# added by Anaconda3 4.2.0 installer
export PATH="/Users/zihengchen/anaconda/bin:$PATH"
