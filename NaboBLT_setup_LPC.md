## Setup GPU Interface on LPC
First log into lpc GPU node `ssh -Y username@cmslpcgpu1.fnal.gov`

if you have not installed local anaconda python, do it with
```bash
wget https://repo.anaconda.com/archive/Anaconda3-2020.02-Linux-x86_64.sh
bash Downloads/Anaconda3-2020.02-Linux-x86_64.sh -b -u -p /uscms_data/d3/zchen/anaconda
```
Then source CUDA and anaconda environment `source SetupCUDA.sh` (.sh file [here](https://github.com/ZihengChen/Notebook/blob/master/LPC_SetupCUDA.sh) ) and you should be able to see `nvidia-smi`, `nvcc --version` and `which python`. It is helpful to refer the [guidance twiki of LPC GPU](https://twiki.cern.ch/twiki/bin/view/Main/GPUSoftwareInstallConfigure) . Then install some python package.

```bash
pip install --user uproot pycuda
conda install pyopencl
conda install ocl-icd-system
conda install pocl
```
After doing this, you can try python
```python
import pyopencl as cl
cl.get_plotforms()
# should prints the following:
# [ <pyopencl.Platform 'NVIDIA CUDA' at 0x56319edefbb0>, 
#   <pyopencl.Platform 'Portable Computing Language' at 0x7f99c2d7f020>]
``` 
Now, you are all set on LPC. Get NanoBLT and have fun.
```bash
git clone https://github.com/ZihengChen/NanoBLT.git
```
On eos LPC, nanoAOD files of EGamma_Run2018 dataset are located at `/eos/uscms/store/user/zchen/nanoaod/data`

