'''
Created on Aug 18, 2012

@author: leo
'''
import unittest
from fruitpunch import Element, App, Scene, Sprite, Collector

# -----------------------------------------------------------------------------
# Stub classes
# -----------------------------------------------------------------------------

class TestApp(App):
    def on_init(self, event):
        self.go_to_scene(self.scene)

class TestScene(Scene):
    def on_init(self, ev):
        el = ElImpl()
        self.add(el)
        self.element = el

class ElImpl(Element):
  
    def on_add(self, event):
        self.added = True
        self.rendered = 0
        
    def on_render(self, event):
        self.rendered += 1

# -----------------------------------------------------------------------------
# Test Class
# -----------------------------------------------------------------------------

class TestElement(unittest.TestCase):

    def setUp(self):
        self.el1 = ElImpl()
        self.el2 = ElImpl()
        self.el1.added = False
        self.el2.add(self.el1)

    def tearDown(self):
        pass

    def testOnAdd(self):
        self.assertTrue(self.el1.added, "onAdd not firing")
        print(self.el2.__dict__)
        self.assertTrue(self.el2.__dict__ == self.el1.parent.__dict__, "could not identify my parent")
    
     
    def testParentAsReference(self):
        self.el1.parent.test = "works"
        self.assertEqual("works", self.el2.test, "parent is not being stored as instance")
        
    def testOnRender(self):
        scene = TestScene()
        app = TestApp()
        app.scene = scene
        app.init()
        
        self.assertEqual(scene.element.rendered, 0)
        
        for i in range(10):
            scene.render_frame()
            
        self.assertEqual(scene.element.rendered, 10)
        
    def testRemove(self):
        el1 = ElImpl()
        el2 = ElImpl()
        
        self.assertEqual(el2.parent, None)
        el1.add(el2)
        self.assertEqual(el2.parent, el1)
        
        el2.parent.remove(el2)
        
        self.assertEqual(el2.parent, None)
        
    def testChildren(self):
        el1 = ElImpl()
        el2 = ElImpl()
        el3 = ElImpl()
        
        el2.identifier = "leo"
        
        el1.add(el2)
        el1.add(el3)
        
        self.assertEqual(2, len(el1.children))
        self.assertEqual(el2.identifier, el1.children[0].identifier)
        pass
