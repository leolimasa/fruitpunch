from fruitpunch.native.native_class import NativeClass
import libfp_core


class Collection(NativeClass):
    
    def __init__(self):
        NativeClass.__init__(self)
        
        self.store(libfp_core.Collection())
    
    def __iter__(self):
        return self.get_iterator()
    
    def __getitem__(self, index):
        return self.get(index)
    
    def __len__(self):
        return self.get_size()
    
    def get_first(self):
        return self.run_native("get_first")
    
    def get_last(self):
        return self.run_native("get_last")
    
    def get(self, i):
        return self.run_native("get", i)
    
    def get_iterator(self):
        return self.run_native("get_iterator")
    
    def get_size(self):
        return self.run_native("get_size")
    
    def is_empty(self):
        return self.run_native("is_empty")
    
NativeClass.class_map[libfp_core.Collection] = Collection