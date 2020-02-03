'''
Created on Apr 21, 2013

@author: leo
'''
from fruitpunch.native.common.prop import Property

class AttributeProperty(Property):
    '''
    Provides a property that sets and gets attributes from a python object.
    '''


    def __init__(self, instance=None, attribute=None):
        '''
        Constructor
        '''
        super(AttributeProperty, self).__init__()
        
        self.instance = instance
        self.attribute = attribute
        
    # _________________________________________________________________________
        
    def get(self):
        '''
        Returns the value of the attribute specified by self.attribute
        onto self.instance. For example, if self.attribute is "test"
        and self.instance is myobj, this will return myobj.test
        '''
        
        if not hasattr(self.instance, self.attribute):
            raise Exception("Attribute or instance has not been set")
        
        return getattr(self.instance, self.attribute)
    
    # _________________________________________________________________________
        
    def set(self, value):
        '''
        Sets the value of the attribute specified by self.attribute
        in self.instance. For example, if self.attribute is "test"
        and self.instance is myobj, this will set myobj.test = value
        '''
        
        if not hasattr(self.instance, self.attribute):
            raise Exception("Attribute or instance has not been set")
        
        return setattr(self.instance, self.attribute, value)
        
        
    
        