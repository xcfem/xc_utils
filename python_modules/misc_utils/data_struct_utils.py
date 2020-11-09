# -*- coding: utf-8 -*-
''' String manipulation utilities. '''
from __future__ import print_function
from __future__ import division

__author__= "Luis C. Pérez Tato (LCPT)"
__cppyright__= "Copyright 2014 LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"

import re
import unicodedata

def remove_accents(input_str):
    nfkd_form = unicodedata.normalize('NFKD', unicode(input_str,'utf-8'))
    only_ascii = nfkd_form.encode('ASCII', 'ignore')
    return only_ascii

def slugify(s):
    """
    Simplifies ugly strings into something URL-friendly.
    >>> print(slugify("[Some] _ Article's Title--"))
    some-articles-title
    """

    # "[Some] _ Article's Title--"
    # "[some] _ article's title--"
    s = s.lower()

    # "[some] _ article's_title--"
    # "[some]___article's_title__"
    for c in [' ', '-', '.', '/']:
        s = s.replace(c, '_')

    # "[some]___article's_title__"
    # "some___articles_title__"
    s = re.sub('\W', '', s)

    # "some___articles_title__"
    # "some   articles title  "
    s = s.replace('_', ' ')

    # "some   articles title  "
    # "some articles title "
    s = re.sub('\s+', ' ', s)

    # "some articles title "
    # "some articles title"
    s = s.strip()

    # "some articles title"
    # "some-articles-title"
    s = s.replace(' ', '-')

    return s


def get_closest_inlist(lst,value):
    '''Return the number in a list that is 
    the closest to the target value.

    :param lst: list of numbers
    :param value: target value. 
    '''
    closest_value=min(lst, key=lambda list_value : abs(list_value - value))
    return closest_value

def get_index_closest_inlist(lst,value):
    '''Return the index in a list that matches 
    the closest element to the target value.

    :param lst: list of numbers.
    :param value: target value. 
    '''
    closest_value=get_closest_inlist(lst,value)
    return lst.index(closest_value)

def remove_duplicates_list(lst):
    '''Return a list from lst without items duplicated
    '''
    return list(dict.fromkeys(lst))
