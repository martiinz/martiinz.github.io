# Install Miniconda and cling on WSL
Quick installation instruction for Miniconda and the C++ environment cling

## Install Miniconda
follow the installation instructions on 
https://docs.conda.io/en/latest/miniconda.html

```bash
bash Miniconda3-latest-Linux-x86_64.sh
#add PATH in .bash_rc
PATH=$PATH:/home/mas/miniconda3/bin
```

## Install Cling 
follow the instructions for cling
https://github.com/jupyter-xeus/xeus-cling/

```bash
conda create -n cling
conda activate cling
conda install xeus-cling -c conda-forge
conda install jupyterlab -c conda-forge
jupyter-lab --no-browser
```
and open http://127.0.0.1:8888

## and maybe some convinience
may add some link and aliases
```bash
ln -s /mnt/c/Users/mas/Documents/ Documents
ln -s /mnt/c/Users/mas/Downloads/ Dowloads
# in .bash_rc
alias jup='cd /home/mas/Documents/py_notebooks/ && jupyter-lab --no-browser'
```
