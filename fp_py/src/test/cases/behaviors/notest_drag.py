'''
Created on 2012-08-12

@author: leo
'''
import unittest
from fruitpunch.behaviors.drag import Drag
from fruitpunch import Sprite, Scene, Point, Event

class TestDrag(unittest.TestCase):


    def setUp(self):
        self.drag = Drag()
        scene = Scene()
        self.sprite = Sprite("tuqui.png")
        self.sprite.scene = scene
        self.sprite.add(self.drag)
        self.scene = scene

    def tearDown(self):
        pass

    def testInit(self):
        self.assertEqual(True, self.drag.enabled, "Whether drag is enabled")
        self.assertEqual(0, self.drag.delta.x, "Amount of position")
        
    def testEvents(self):
        self.drag.dragging = False
        self.sprite.notify(Event("pointer_down"))
        self.assertTrue(self.drag.dragging, "Drag not fired after pointer down")
        
    def testRender(self):
        p = Point()
        p.x = 0
        p.y = 0
        self.scene.window.pointer = p
        self.sprite.left = 0
        self.sprite.top = 0
        self.drag.on_render(self.scene)
        
        self.sprite.notify(Event("pointer_down"))
        p.x = 10
        self.scene.window.pointer = p
        self.drag.on_render(self.scene)
        self.assertEqual(10, self.sprite.left, "Sprite not moved on x")
        self.assertEqual(0, self.sprite.top, "Sprite moved on Y when its not supposed to")
        self.sprite.notify(Event("pointer_up"))
        
        self.sprite.notify(Event("pointer_down"))
        p.y = 10
        self.scene.window.pointer = p
        self.drag.on_render(self.scene)
        self.assertEqual(10, self.sprite.left, "Sprite moved on X when its not supposed to")
        self.assertEqual(10, self.sprite.top, "Sprite not moved on Y")
        self.sprite.notify(Event("pointer_up"))
        
        p.y = 20
        self.scene.window.pointer = p
        self.drag.on_render(self.scene)
        self.assertEqual(10, self.sprite.left, "Sprite moved when not dragging")
        self.assertEqual(10, self.sprite.top, "Sprite moved when not dragging")
        
        # tests the last position
        self.sprite.notify(Event("pointer_down"))
        p.y = 15
        self.scene.window.pointer = p
        self.drag.on_render(self.scene)
        p.y = 30
        self.scene.window.pointer = p
        self.drag.on_render(self.scene)
        self.assertEqual(30, self.drag.last_pos.y, "last position not being updated")
        
        
        