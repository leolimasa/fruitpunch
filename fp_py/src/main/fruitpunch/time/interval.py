'''
Created on Apr 6, 2013

@author: steven
'''

from fruitpunch.native.elements.element import Element
import time

class Interval(Element):
    '''
    this class allows things to happen
    after a certain duration of time has elapsed
    
    @ivar interval decimal: how many seconds to wait. .15 for 1/5 of a second.
    @ivar func function: function to perform after set time interval elapsed
    '''
    # _____________________________________________________________________

    def __init__(self, interval, func, loop=True):
        super(Interval, self).__init__()
        self.loop = loop
        self.called_once = False
        self.interval = interval
        self.func = func
        self._begin_interval_time = time.time()            
    # _____________________________________________________________________
    
    def on_add(self, ev):
        self.parent.listen({"post_render": self.on_render})
    # _____________________________________________________________________     

    def on_render(self, ev):
        '''
        if its set to loop keep going
        if not...then only do it once...
        '''
        if self.loop == False and self.called_once == True:
            return 
        if time.time() - self._begin_interval_time >= self.interval:
            self.func()
            self.called_once = True
            self._begin_interval_time = time.time()
                
            
    
        
    
    
        