from externalTools.fastDownwardParser import pddl_parser, normalize

def __fastDownwardParse(domainFile, problemFile):
    """uses fast downward to parse PDDL files into a python readable format"""
    problem = pddl_parser.open(domainFile, problemFile)
    normalize.normalize(problem)
    return problem

def parse(domainFile, problemFile):
    """parses the given PDDL files into a python readable format"""
    return __fastDownwardParse(domainFile, problemFile)