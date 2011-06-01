#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest as ut
import pyvle
import sys

filename = sys.argv[1]

class TestExperiment(ut.TestCase):

    def setUp(self):
        self.exp = pyvle.Vle(filename)

    def testGetBegin(self):
        self.assertEqual(0, self.exp.getBegin())

    def testSetBeginBadInput(self):
        self.assertRaises(Exception, self.exp.setBegin, 'a')

    def testSetBegin(self):
        self.exp.setBegin(1)
        self.assertEqual(1, self.exp.getBegin())


if __name__ == '__main__':
    ut.main()
