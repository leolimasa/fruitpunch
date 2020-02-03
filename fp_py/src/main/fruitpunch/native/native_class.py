'''
Created on Oct 22, 2012

@author: leo
'''

from libfp_core import Object
import libfp_core
import weakref

class NativeClass(object):
    '''
    Acts as a bridge between native (C++) classes and python classes. It acts 
    upon two distinct concepts: python instances and native instances. Python
    instances are objects created on the python side; native instances are 
    native C++ instances that are accessed through its python bindings. 
    This class' main job is to maintain a dictionary that links object ids 
    with python instances, so when to_python is called it knows what native 
    instance refers to what python instance and therefore keeps attributes in
    synch.
    '''
    
    instance_store = weakref.WeakValueDictionary()
    class_map = {} # maps native classes to python types
    
    def __init__(self):
        self.keep_instances = {}

    def store(self, native_instance):
        '''
        Sets the native instance of this object to native_instance and stores
        it in the instance_store alongside the object id.
        '''
        self._native = native_instance
        self._native.set_py_object(self)
        
        if not hasattr(native_instance, "instance_id"):
            raise Exception(str(native_instance) + " has no instance_id property.")
        
        if isinstance(native_instance, NativeClass):
            raise Exception(str(native_instance) + " is not an instance of NativeClass. Make sure self.store() was called properly.")
        
        #NativeClass.instance_store[native_instance.instance_id] = self
    
    # _____________________________________________________________________
    def keep(self, instance):
        '''
        Ensures that the specified object instance will have the same
        lifetime as the current object. This is used to prevent python
        objects from being destroyed by the garbage collector when
        they still exist in the C++ side
        '''        
        #self.keep_instances[id(instance)] = instance
        
    # _____________________________________________________________________
    
    def let_go(self, instance):
        '''
        Signifies that the specified instance does not belong to the
        current object anymore and can be collected by the Python 
        garbage collector when necessary. This is the opposite of
        keep()
        '''
        #idval = id(instance)
        #if self.keep_instances.has_key(idval):
        #    self.keep_instances.pop(idval)
    
    # _____________________________________________________________________
        
    def run_native(self, method_name, *args):
        '''
        Runs a method from the native class and calls to_python
        in the result so it converts to a user defined python
        object.
        '''
        method = getattr(self._native, method_name)
        
        new_args = []
        for arg in args:
            if isinstance(arg,NativeClass):
                arg = arg._native
            new_args.append(arg)
        
        result = method(*new_args);
        return NativeClass.to_python(result)
        
    # _____________________________________________________________________
    
    @staticmethod
    def to_python(native_instance):
        '''
        Looks up an entry in NativeClass.instance_store that matches the id 
        returned by native_instance.instance_id, and returns it. If it does not 
        find it, creates a new instance of python class and returns that. All 
        the attributes of native_instance will be merged into the resulting object.
        '''
        
        # no object, no result
        if native_instance is None:
            return None
        
        # if its not an Object, then it is most likely a primitive type
        if not isinstance(native_instance, Object):
            return native_instance
        
        pyobj = native_instance.get_py_object()
        
        # if it's none, it means we never initialized this instance from the
        # python side.
        if pyobj is None:
            if not native_instance.__class__ in NativeClass.class_map.keys():
                raise Exception(str(native_instance.__class__) + " has no known Python equivalent.")
            pyobj = NativeClass.class_map[native_instance.__class__]()
            pyobj._native = native_instance
            native_instance.set_py_object(pyobj)
        
        return pyobj
        
        # Returns the stored instance or a new instance of py_class()
        #if native_instance.instance_id in NativeClass.instance_store.keys():
            #py_instance = NativeClass.instance_store[native_instance.instance_id]
            #NativeClass.merge(native_instance, py_instance)
        #else:
            #if not native_instance.__class__ in NativeClass.class_map.keys():
            #    raise Exception(str(native_instance.__class__) + " has no known Python equivalent.")
            
            #py_instance = NativeClass.class_map[native_instance.__class__]()
            #py_instance._native = native_instance
        
        

    # _____________________________________________________________________
    

        
    
    
        
        
        