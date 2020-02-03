'''
Created on 2012-11-25

@author: Steven
'''
import unittest
from fruitpunch import Sprite, Scene, Point, Event, Body, BodyType, PhysicsWorld, Scene, App
from fruitpunch.behaviors.body_drag import BodyDrag

class TestScene(Scene):
    def on_init(self, ev):
        self.sprite = Sprite("tuqui.png")
	self.world = PhysicsWorld()

	self.add(self.world)
	self.add(self.sprite)

        self.sprite_body = Body(BodyType.kinematic)
	self.sprite.add(self.sprite_body)

	self.body_drag = BodyDrag(self.sprite_body)
	self.sprite.add(self.body_drag)

class TestApp(App):
    def on_init(self, event):
        self.go_to_scene(self.scene)

class TestDrag(unittest.TestCase):
    def setUp(self):
	app = TestApp()
	self.scene = TestScene()
	app.scene = self.scene
	app.init()
        
    def tearDown(self):
        pass
        
