'''
Created on Feb 13, 2013

@author: leo
'''
import unittest
import fruitpunch.behaviors
import fruitpunch.native
from fruitpunch import Node, Sprite, PhysicsWorld
import pydevd
import sys

#pydevd.settrace()

class Node1:
    
    def __init__(self):
        self.children = []
    
    def add(self, obj):
        self.children.append(obj)
        
class Node2(Node1):
    pass

class TestNode(unittest.TestCase):


    def setUp(self):
        pass


    def tearDown(self):
        pass


    def testSearchClass(self):
        paths = [fruitpunch.behaviors, fruitpunch.native]
        
        node = Node()
        
        body_drag_class = node._search_class("bodydrag", paths)
        collector_class = node._search_class("collector", paths)
        body_class = node._search_class("body", paths)
        
        self.assertEqual(body_drag_class, fruitpunch.behaviors.body_drag.BodyDrag)
        self.assertEqual(collector_class, fruitpunch.behaviors.collector.Collector)
        self.assertEqual(body_class, fruitpunch.native.physics.body.Body)
        
        body_class = node._search_class("body", fruitpunch)
        self.assertEqual(body_class, fruitpunch.native.physics.body.Body)
    
    def testInflate(self):
        Node.default_module_paths = sys.modules[__name__]
        
        sprite = Node()
        sprite.name = "node1"
        spriteAttrs = Node()
        spriteAttrs.name = "@attributes"
        spriteWidth = Node()
        spriteWidth.name = "scale"
        spriteWidth.value = "0.5"
        
        spriteAttrs.add(spriteWidth)
        sprite.add(spriteAttrs)
        
        body = Node()
        body.name = "node2"
        bodyAttrs = Node()
        bodyAttrs.name = "@attributes"
        bodyVar = Node()
        bodyVar.name = "myprop"
        bodyVar.value = "myval"
        
        bodyAttrs.add(bodyVar)
        body.add(bodyAttrs)
        sprite.add(body)
        
        # test with default module paths
        real_sprite = sprite.inflate()
        self.assertTrue(isinstance(real_sprite, Node1))
        self.assertEqual(1, len(real_sprite.children))
        self.assertEqual(0.5, real_sprite.scale)
        self.assertTrue(isinstance(real_sprite.children[0], Node2))
        self.assertEqual("myval", real_sprite.children[0].myprop)
        
        
        sprite.module_paths = sys.modules[__name__]
        real_sprite = sprite.inflate()
        
        self.assertTrue(isinstance(real_sprite, Node1))
        self.assertEqual(1, len(real_sprite.children))
        self.assertEqual(0.5, real_sprite.scale)
        self.assertTrue(isinstance(real_sprite.children[0], Node2))
        self.assertEqual("myval", real_sprite.children[0].myprop)
        