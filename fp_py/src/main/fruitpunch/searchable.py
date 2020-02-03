'''
Created on Feb 16, 2013

@author: leo
'''

class Searchable(object):
    '''
    Allows classes that have a "children" array to be searched
    by using some convenience methods.
    '''

    def find_by(self, attr, value=None):
        '''
        Returns the first child that has an attr that is equal to value.
        If value is not defined, then it will return the first child that
        has that attribute defined.
        '''
        
        for child in self.children:
            if hasattr(child, attr): 
                if (value is not None and getattr(child, attr) == value) \
                or value is None:
                    return child
            
            result = Searchable.find_by(child, attr, value)
            if result is not None:
                return result
        return None
    
    # _________________________________________________________________________
    
    def find_all_by(self, attr, value=None):
        '''
        Returns all the children that has an attr that is equal to value.
        If value is not defined, then it will return all the children that have
        the attribute defined.
        '''
        result = []
        
        for child in self.children:
            if hasattr(child, attr): 
                if (value is not None and getattr(child, attr) == value) \
                or value is None:
                    result.append(child)
            
            recurse = Searchable.find_all_by(child, attr, value)
            result += recurse
        return result
        
    # _________________________________________________________________________
    
    def find_all_by_class(self, clazz):
        '''
        Returns all the children that is an instance of the specified class
        '''
        
        result = []
        
        for child in self.children:
            if isinstance(child, clazz):
                result.append(child)
            
            extra_results = Searchable.find_all_by_class(child, clazz)
            result += extra_results
        
        return result
    
    # _________________________________________________________________________
    
    def find_by_class(self, clazz):
        '''
        Returns the first child that is an instance of the specified class
        '''
        
        for child in self.children:
            if isinstance(child, clazz):
                return child
            
            result = Searchable.find_by_class(child, clazz)
            if result is not None:
                return result
        
        return None