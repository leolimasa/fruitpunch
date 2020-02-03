import unittest
from fruitpunch import SpriteSheet, Frame, Element, Sprite

class TestSpriteSheet(unittest.TestCase):
    
    def setUp(self):
        self.sprite = Sprite("pedoBear.png")
        
        self.frame1 = Frame()
        self.frame2 = Frame()
        
        self.frame1.width = 100
        self.frame1.height = 200
        
        self.frame2.width = 50
        self.frame2.height = 60
        
        self.sheet = SpriteSheet()
        self.sheet.add(self.frame1)
        self.sheet.add(self.frame2)
        self.sprite.add(self.sheet)

    def tearDown(self):
        pass
    
    def testAddAndRemove(self):
        sheet = SpriteSheet()
        frame = Frame()
        sheet.add(frame)
        
        self.assertEqual(sheet.frames[0], frame)
        
        element = Element()
        sheet.add(element)
        self.assertEqual(len(sheet.frames), 1)
        self.assertEqual(len(sheet.children), 2)
        
        sheet.remove(frame)
        self.assertEqual(len(sheet.frames), 0)
        self.assertEqual(len(sheet.children), 1)
        
    def testResize(self):
        self.sheet.resize(0)
        self.assertEqual(self.sprite.width, 100)
        self.assertEqual(self.sprite.height, 200)
        
        self.sheet.resize(1)
        self.assertEqual(self.sprite.width, 50)
        self.assertEqual(self.sprite.height, 60)
    
    def testRenderSingle(self):
        
        self.sheet.render_single(0)
        self.assertEqual(self.sprite.width, 100)
        self.assertEqual(self.sprite.height, 200)
        
        self.sheet.lock_width = True
        self.sprite.width = 200
        self.sheet.render_single(0)
        self.assertEqual(self.sprite.width, 200)
        self.assertEqual(self.sprite.height, 400)
        
        self.sheet.lock_height = True
        self.sheet.lock_width = False
        self.sprite.height = 500
        self.sheet.render_single(0)
        self.assertEqual(self.sprite.width, 250)
        self.assertEqual(self.sprite.height, 500)
        
        