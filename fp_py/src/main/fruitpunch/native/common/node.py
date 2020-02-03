from fruitpunch.native.native_class import NativeClass
from os.path import dirname
import libfp_core
import inspect

class Node(NativeClass):
    '''
    A single Node of a tree structure. A Node is an abstract representation
    of a part of a tree. It has children and parent. Nodes are usually
    generated from files or processes that describe tree structures, such as
    XML or JSON. 
    '''
    
    default_module_paths = []

    # _________________________________________________________________________

    def __init__(self, file=None):
        NativeClass.__init__(self)
        
        self.auto_cast_numbers = True
        self.module_paths = []
        
        if file:
            self.store(libfp_core.Node(file))
        else:
            self.store(libfp_core.Node())
    
    # _________________________________________________________________________
            
    def inflate(self):
        '''
        Converts the entire node tree to actual object instances, where
        the object instances will be classes matching the node name.
        '''
        
        clazz = None
        
        # Search for a class with the same name of the node in the package
        # paths
        clazz = self._search_class(self.name, self.module_paths)
        if clazz is None:
            clazz = self._search_class(self.name, Node.default_module_paths)
        if clazz is None:
            raise Exception("Could not find class with name '" + self.name + "'.")
        
        # Instantiates the class
        instance = clazz()
        
        # Inflates the children
        self.inflate_children_to(instance)
        
        return instance
    
    # _________________________________________________________________________
    
    def inflate_children_to(self, dest):
        '''
        Calls inflate() on each child of this node, and passes the
        resulting object as an argument to add() of dest
        '''
        
        # Processes the children
        for child in self.children:
            
            # Processes attributes
            if child.name == "@attributes":
                for attr in child.children:
                    
                    # Check if we can cast it to number. If not, go with the
                    # regular attribute
                    if self.auto_cast_numbers \
                    and attr.value_as_number() is not None:
                        setattr(dest, attr.name, attr.value_as_number())
                    else:
                        setattr(dest, attr.name, attr.value)
            
            # Processes the real child nodes
            elif child.name[0] != "@":
                child.module_paths = self.module_paths
                inflated = child.inflate()
                dest.add(inflated)
    
    # _________________________________________________________________________
    
    def value_as_number(self):
        '''
        Tries to return the value as a number. Will return None if it
        fails to convert. Will return a float if it succeeds.
        '''
        try:
            float(self.value)
        except ValueError:
            return None
        
        return float(self.value)
    
    # _________________________________________________________________________    
        
    def _search_class(self, class_name, module):
        '''
        Traverses the specified module in search of a class named class_name.
        This function is recursive, and will traverse the entire 
        package/module tree.
        
        @ivar class_name: A string which contains the class name
        @ivar module_paths: A List that contains module objects to be searched, 
                            or a single module 
        '''
        
        
        clazz = None        
        
        # ---------------------------------------------------------------------
        # Processes a list of modules
        # ---------------------------------------------------------------------
        if isinstance(module, list):
            for m in module:
                clazz = self._search_class(class_name, m)
                if clazz is not None:
                    break
            return clazz
        
        # ---------------------------------------------------------------------
        # Processes a single module
        # ---------------------------------------------------------------------
        for key, entry in module.__dict__.iteritems():
            
            # If the module is a package, then we search it's children for 
            # modules
            if module.__package__ is None and inspect.ismodule(entry):
                clazz = self._search_class(class_name, entry)
                if clazz is not None:
                    return clazz
            
            # It's a real module, so we search for classes
            else:

                if inspect.isclass(entry) and \
                entry.__name__.lower() == class_name.lower():
                    return entry
            
        return clazz
        
            

    # -------------------------------------------------------------------------
    # Native Methods
    # -------------------------------------------------------------------------

    # _________________________________________________________________________

    def get_children(self):
        return self.run_native("get_children")
    # _________________________________________________________________________

    def get_parent(self):
        return self.run_native("get_parent")
    # _________________________________________________________________________

    def set_parent(self, parent):
        return self.run_native("set_parent", parent)
    # _________________________________________________________________________

    def get(self, name):
        '''
        Searches and returns the first child node with the specified name.
        This method is case insensitive. Returns a null pointer if it cannot find the node.
        '''

        return self.run_native("get", name)
    # _________________________________________________________________________

    def add(self, node):
        return self.run_native("add", node)
    # _________________________________________________________________________

    def remove(self, node):
        return self.run_native("remove", node)
    # _________________________________________________________________________

    def get_name(self):
        return self.run_native("get_name")
    # _________________________________________________________________________

    def set_name(self, name):
        return self.run_native("set_name", name)
    # _________________________________________________________________________

    def get_namespace(self):
        return self.run_native("get_namespace")
    # _________________________________________________________________________

    def set_namespace(self, _namespace):
        return self.run_native("set_namespace", _namespace)
    # _________________________________________________________________________

    def get_value(self):
        return self.run_native("get_value")
    # _________________________________________________________________________

    def set_value(self, value):
        return self.run_native("set_value", value)

    # -------------------------------------------------------------------------
    # Properties
    # -------------------------------------------------------------------------

    children = property(get_children)
    parent = property(get_parent, set_parent)
    name = property(get_name, set_name)
    namespace = property(get_namespace, set_namespace)
    value = property(get_value, set_value)

NativeClass.class_map[libfp_core.Node] = Node