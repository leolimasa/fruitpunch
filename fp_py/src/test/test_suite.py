'''
Created on Aug 15, 2012

@author: leo
'''
import unittest
import os
import pydevd
#import pydevd

def init(runtime):
    #from results.results_app import ResultsApp
    
    #pydevd.settrace()
    loader = unittest.TestLoader()
    #suite.loadTestsFromTestCase(Test)
    
    test_runner = unittest.TextTestRunner()
    results = test_runner.run(loader.discover("cases"))
    #app = ResultsApp()
    #app.results = results 
    #app.init()
    
if __name__ == "__main__":
    from runner import runner
    
    runner.run(os.path.abspath(__file__))
