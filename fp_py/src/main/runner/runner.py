'''
Created on 2012-08-19

@author: leo
'''
import os
from subprocess import call

from os import environ, getcwd

def generate_basedir():
    '''
    Returns an absolute path to where is the maven basedir
    of this project. It will go up the tree until it finds a
    pom.xml, and will return that path.
    '''
    current_path = os.path.abspath(getcwd())
    current_dir = os.path.dirname(current_path)
    
    while current_dir.__len__() > 0:
        for f in os.listdir(current_dir):
            if os.path.basename(f) == "pom.xml":
                print("Base directory: " + f)
                return current_dir
        current_dir = os.path.dirname(current_dir)
        
    raise Exception("Could not find the maven base directory. This means that I could not find a pom.xml.")

def generate_python_paths():
    '''
    Returns a string with all the directories in the PYTHONPATH,
    preceeded by a "-p", such as: -p "/home/leo" -p "/usr/lib/python"
    This is intended to be used as a command line argument for fp_emu
    '''
    
    if not "PYTHONPATH" in os.environ.keys():
        return ""
    
    paths = os.environ['PYTHONPATH'].split(os.pathsep)
    result = ""
    for path in paths:
        result += ' -p "' + path + '"';
        
    return result

def find_fp_emu():
    '''
    Looks for fp_emu in the pythonpath
    '''
    paths = os.environ['PYTHONPATH'].split(os.pathsep)
    for path in paths:
        if not os.path.exists(path):
            continue
        
        for f in os.listdir(path):
            full_path = os.path.join(path, f)
            if f == "fp_emu" and os.path.isfile(full_path):
                return full_path
    
    raise Exception("Could not find the fp_emu binary. Make sure it is in your PYTHONPATH.")

def find_resources_dir():
    '''
    Looks for a folder named "resources" or "res"
    in the pythonpath and returns it
    '''
    paths = os.environ['PYTHONPATH'].split(os.pathsep)
    for path in paths:
        bname = os.path.basename(path)
        
        if (bname == "resources") or (bname == "res"):
            return path
        
    print("WARNING: Could not find a resources folder. Make sure you have it in your PYTHONPATH.")
    return None     

def run(file_path):
    
    fpemu = find_fp_emu()
    #resourcepath = find_resources_dir()
    base = generate_basedir()
    libsdir = os.path.join(base, "target", "dependencies", "linux", "lib")
    
    
    fpemu_dir = os.path.dirname(fpemu)
    #cmd = fpemu + pythonpath + ' -r "' + resourcepath + '" "' + file_path + '"'
    cmd = "export LD_LIBRARY_PATH=" + libsdir + ";"
    cmd += "cd " + fpemu_dir + ";"
    cmd += './fp_emu "' + file_path + '"'
    
    #if resourcepath:
    #    cmd += " -r " + resourcepath
        
    print(cmd)
    call(cmd, shell=True)
    
def run_scene(scene):
    from fruitpunch.runner_app import RunnerApp
    
    app = RunnerApp(scene)
    app.init()