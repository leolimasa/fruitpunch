import unittest
from fruitpunch.graphics.frame_set import FrameSet

class TestSpriteSheet(unittest.TestCase):
    def setUp(self):
        pass
    
    def testLoadFrames(self):
        fset = FrameSet()
        fset.frames = "3-7,10-12"
        
        self.assertEqual(fset.frame_map[0], 3)
        self.assertEqual(fset.frame_map[1], 4)
        self.assertEqual(fset.frame_map[2], 5)
        self.assertEqual(fset.frame_map[3], 6)
        self.assertEqual(fset.frame_map[4], 7)
        self.assertEqual(fset.frame_map[5], 10)
        self.assertEqual(fset.frame_map[6], 11)
        self.assertEqual(fset.frame_map[7], 12)