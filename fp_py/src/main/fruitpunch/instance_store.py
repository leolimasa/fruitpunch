'''
Created on 2012-09-25

@author: leo
'''

class InstanceStore(object):
    '''
    classdocs
    '''
    store = {}

    def __init__(self):
        '''
        Constructor
        '''
    
    @staticmethod
    def store(native):
        if hasattr(native, "instance_id"):
            InstanceStore.store[native.instance_id] = native
    
    @staticmethod
    def retrieve(native):
        original = InstanceStore.store[native.instance_id];
        
        # Copy all properties from native to original
        original.__dict__.update(native.__dict__)
        
        return original
        