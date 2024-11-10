from __future__ import annotations
from typing import Hashable, Dict

from graphviz import Digraph

class TrieNode:
    __counter = 0
    def __init__(self, tag: Hashable):
        self.uid = TrieNode.__counter
        TrieNode.__counter += 1
        self.tag: Hashable = tag
        self.children: Dict[Hashable, TrieNode]  = {}

    def addChild(self, child: TrieNode) -> None:
        self.children[child.tag] = child

    def hasAnyChild(self) -> bool:
        return self.children.get() != None

    def __str__(self) -> str:
        return f'TrieNode(uid: {self.uid}, \'{self.tag}\': {list(self.children.keys())})'

class Trie:
    def __init__(self):
        self.root: TrieNode = TrieNode('')
    
    def insertWord(self, word: str) -> None:
        current_node = self.root

        for character in word:
            if current_node.children.get(character):
                current_node = current_node.children[character]
                continue
            else:
                newNode = TrieNode(character)
                current_node.addChild(newNode)
                current_node = newNode

    @staticmethod
    def __display(root: Trie) -> None:
        if root:
            for child in root.children.values():
                print(child)
                Trie.__display(child)

    def display(self) -> None:
        Trie.__display(self.root)

    @staticmethod
    def __displayImage(graph, node, node_label):
        if node:
            node_label += node.tag
            graph.node(str(node.uid), label=node_label)
            for child in node.children.values():
                node_idx = Trie.__displayImage(graph, child, node_label)
                graph.edge(str(node.uid), str(child.uid), label=child.tag)
    
    def displayImage(self) -> None:
        G = Digraph()
        Trie.__displayImage(G, self.root, '')
        G.render('graph', view=True)
        G.render(view=True)


tokens = [
    '%c',
    '%%',

    '%hi',
    '%hu',
    '%i',
    '%u',
    '%li',
    '%lu',
    '%lli',
    '%llu',

    '%f',
    '%lf',
    '%llf',

    '%u8',
    '%u16',
    '%u32',
    '%u64',

    '%i8',
    '%i16',
    '%i32',
    '%i64',

    '%s'
]

trie = Trie()

for token in tokens:
    trie.insertWord(token)

trie.display()
trie.displayImage()
