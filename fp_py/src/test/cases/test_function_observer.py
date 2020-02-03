'''
Created on Apr 20, 2013

@author: leo
'''
import unittest
from fruitpunch import Animation, Observer, Event

       

class Test(unittest.TestCase):


    def setUp(self):
        pass


    def tearDown(self):
        pass

    def myevent(self, e):
        self.source = e.source

    def testSource(self):
        anim = Animation()
        anim.listen({"myevent":self.myevent})
        anim.notify(Event("myevent"))
        self.assertEqual(anim, self.source)
        