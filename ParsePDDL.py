from fastDownwardParser import pddl_parser, normalize
def fastDownwardParse(domainFile, problemFile):
    #all credit for parsing of PDDL files goes to Fast Downward and its contributors
    # Helmert M, Richter S, Westphal M, Karpas E, Katz M and Röger G
    problem = pddl_parser.open(domainFile, problemFile)
    normalize.normalize(problem)
    return problem
def parse(domainFile, problemFile):
    return fastDownwardParse(domainFile, problemFile)