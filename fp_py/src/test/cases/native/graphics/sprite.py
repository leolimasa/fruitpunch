'''
Created on Feb 16, 2013

@author: leo
'''
import unittest
from fruitpunch import Sprite


class SpriteTest(unittest.TestCase):


    def testImageUrl(self):
        sprite = Sprite()
        sprite.image_url = "orange.png"
        self.assertEqual(48, sprite.width)
        self.assertEqual(48, sprite.height)
