def ResolutionProp(KB):
    clauses = [set(clause) for clause in KB]
    result = []
    step = 1
    
    for clause in clauses:
        if len(clause) == 1:
            result.append(f"{step} {tuple(clause)}")
        else:
            s = ", ".join([f"{chr(97+i)}{lit}" for i, lit in enumerate(clause)])
            result.append(f"{step} ({s})")
        step += 1
    
    used = set()
    while True:
        new_clause = None
        for i in range(len(clauses)):
            for j in range(i + 1, len(clauses)):
                if (i, j) in used:
                    continue
                used.add((i, j))
                ci, cj = clauses[i], clauses[j]
                for lit_i in ci:
                    for lit_j in cj:
                        if lit_i == "~" + lit_j or lit_j == "~" + lit_i:
                            new_clause = (ci - {lit_i}) | (cj - {lit_j})
                            if new_clause not in clauses:
                                clauses.append(new_clause)
                                idx_i = chr(97 + list(ci).index(lit_i)) if len(ci) > 1 else ""
                                idx_j = chr(97 + list(cj).index(lit_j)) if len(cj) > 1 else ""
                                ref_i = f"{i+1}{idx_i}" if idx_i else f"{i+1}"
                                ref_j = f"{j+1}{idx_j}" if idx_j else f"{j+1}"
                                if len(new_clause) == 0:
                                    result.append(f"{step} R[{ref_i},{ref_j}] = ()")
                                    return result
                                else:
                                    s = ", ".join(sorted(new_clause))
                                    result.append(f"{step} R[{ref_i},{ref_j}] = ({s})")
                                step += 1
        if new_clause is None:
            break
    return result


def MGU(atom1, atom2):
    def parse_atom(atom):
        predicate = atom[:atom.index('(')]
        arg_str = atom[atom.index('(')+1:atom.rindex(')')]
        args = []
        current = ''
        paren_count = 0
        
        for char in arg_str:
            current += char
            if char == '(':
                paren_count += 1
            elif char == ')':
                paren_count -= 1
            elif char == ',' and paren_count == 0:
                args.append(current[:-1].strip())
                current = ''
        if current:
            args.append(current.strip())
        
        return predicate, args
    
    p1, args1 = parse_atom(atom1)
    p2, args2 = parse_atom(atom2)
    
    if p1 != p2 or len(args1) != len(args2):
        return {}
    
    subst = {}

    def unify(t1, t2, subst):
        if t1 == t2:
            return True
        
        is_var1 = len(t1) > 1 and t1[0].islower() and '(' not in t1
        is_var2 = len(t2) > 1 and t2[0].islower() and '(' not in t2
        
        if is_var1 and t1 in subst:
            return unify(subst[t1], t2, subst)
        if is_var2 and t2 in subst:
            return unify(t1, subst[t2], subst)
        
        if is_var1:
            subst[t1] = t2
            return True
        if is_var2:
            subst[t2] = t1
            return True
        
        if t1.startswith('f(') and t2.startswith('f('):
            f_args1 = t1[2:-1].split(',')
            f_args2 = t2[2:-1].split(',')
            if len(f_args1) != len(f_args2):
                return False
            for a1, a2 in zip(f_args1, f_args2):
                if not unify(a1.strip(), a2.strip(), subst):
                    return False
            return True
        
        return False
    
    for t1, t2 in zip(args1, args2):
        if not unify(t1, t2, subst):
            return {}
    
    def apply_subst(term):
        if len(term) > 1 and term[0].islower() and '(' not in term and term in subst:
            return apply_subst(subst[term])
        return term
    
    final_subst = {k: apply_subst(v) for k, v in subst.items()}
    return final_subst

from typing import List, Tuple, Dict, Set

class Clause:
    def __init__(self, predicates: List[Tuple[str, Tuple[str, ...]]]):
        self.predicates = predicates

    def __str__(self):
        if len(self.predicates) == 1:
            return f"({self.predicates[0][0]}({','.join(self.predicates[0][1])}),)"
        else:
            return "(" + ",".join([f"{p[0]}({','.join(p[1])})" for p in self.predicates]) + ")"

    def __eq__(self, other):
        return isinstance(other, Clause) and set(self.predicates) == set(other.predicates)

    def __hash__(self):
        return hash(tuple(sorted(self.predicates)))

def unify(p1: Tuple[str, Tuple[str, ...]], p2: Tuple[str, Tuple[str, ...]]) -> Dict[str, str] | None:
    if p1[0] != f"~{p2[0]}" and f"~{p1[0]}" != p2[0]:
        return None
    if len(p1[1]) != len(p2[1]):
        return None
    
    substitution = {}
    for arg1, arg2 in zip(p1[1], p2[1]):
        if arg1 == arg2:
            continue
        elif arg1.islower():
            if arg2 in substitution and substitution[arg2] != arg1:
                return None
            substitution[arg2] = arg1
        elif arg2.islower():
            if arg1 in substitution and substitution[arg1] != arg2:
                return None
            substitution[arg1] = arg2
        else:
            if arg1 in substitution and substitution[arg1] != arg2:
                return None
            substitution[arg1] = arg2
    return substitution

def apply_substitution(clause: Clause, substitution: Dict[str, str]) -> Clause:
    new_predicates = []
    for pred, args in clause.predicates:
        new_args = tuple(substitution.get(arg, arg) for arg in args)
        new_predicates.append((pred, new_args))
    return Clause(new_predicates)

def resolve(c1: Clause, c2: Clause) -> Tuple[Clause, Dict[str, str], Tuple[int, int]] | None:
    for i, p1 in enumerate(c1.predicates):
        for j, p2 in enumerate(c2.predicates):
            substitution = unify(p1, p2)
            if substitution is not None:
                new_c1 = apply_substitution(Clause([p for k, p in enumerate(c1.predicates) if k != i]), substitution)
                new_c2 = apply_substitution(Clause([p for k, p in enumerate(c2.predicates) if k != j]), substitution)
                result_preds = list(set(new_c1.predicates + new_c2.predicates))  # 去重
                return Clause(result_preds), substitution, (i, j)
    return None

def ResolutionFOL(KB: Set[Tuple[Tuple[str, Tuple[str, ...]], ...]]) -> List[str]:
    clauses = [Clause(list(clause)) for clause in KB]
    steps = []
    for i, clause in enumerate(clauses, 1):
        steps.append(f"{i} {clause}")
    
    step_num = len(clauses) + 1
    used_clauses = set()
    max_steps = 1000

    while step_num <= max_steps:
        new_clause_found = False
        for i in range(len(clauses)):
            for j in range(i + 1, len(clauses)):
                if (i, j) in used_clauses or (j, i) in used_clauses:
                    continue
                result = resolve(clauses[i], clauses[j])
                if result is not None:
                    resolvent, substitution, (p1_idx, p2_idx) = result
                    subst_str = "{" + ", ".join([f"{k}={v}" for k, v in substitution.items()]) + "}" if substitution else ""
                    p1_label = f"{i+1}{chr(97+p1_idx)}" if len(clauses[i].predicates) > 1 else f"{i+1}"
                    p2_label = f"{j+1}{chr(97+p2_idx)}" if len(clauses[j].predicates) > 1 else f"{j+1}"
                    step = f"{step_num} R[{p1_label},{p2_label}]{subst_str} = {resolvent}"
                    steps.append(step)
                    
                    if not resolvent.predicates:
                        return steps
                    
                    if resolvent not in clauses:  
                        clauses.append(resolvent)
                        used_clauses.add((i, j))
                        new_clause_found = True
                        step_num += 1
                        break
            if new_clause_found:
                break
        if not new_clause_found:
            break
    
    steps.append(f"终止: 达到最大步数 {max_steps} 或无新子句")
    return steps


def test_resolution_fol():

    KB1 = {
        (("GradStudent", ("sue",)),),
        (("~GradStudent", ("x",)), ("Student", ("x",))),
        (("~Student", ("x",)), ("HardWorker", ("x",))),
        (("~HardWorker", ("sue",)),)
    }
    print("\n=== 测试 KB1 ===")
    result1 = ResolutionFOL(KB1)
    for step in result1:
        print(step)
    print("结果:", "正确" if result1[-1].endswith(" = ()") else "错误")

    KB2 = {
        (("A", ("tony",)),),
        (("A", ("mike",)),),
        (("A", ("john",)),),
        (("L", ("tony", "rain")),),
        (("L", ("tony", "snow")),),
        (("~A", ("x",)), ("S", ("x",)), ("C", ("x",))),
        (("~C", ("y",)), ("~L", ("y", "rain"))),
        (("L", ("z", "snow")), ("~S", ("z",))),
        (("~L", ("tony", "u")), ("~L", ("mike", "u"))),
        (("L", ("tony", "v")), ("L", ("mike", "v"))),
        (("~A", ("w",)), ("~C", ("w",)), ("S", ("w",)))
    }
    print("\n=== 测试 KB2 ===")
    result2 = ResolutionFOL(KB2)
    for step in result2:
        print(step)

    KB3 = {
        (("On", ("tony", "mike")),),
        (("On", ("mike", "john")),),
        (("Green", ("tony",)),),
        (("~Green", ("john",)),),
        (("~On", ("xx", "yy")), ("~Green", ("xx",)), ("Green", ("yy",)))
    }
    print("\n=== 测试 KB3 ===")
    result3 = ResolutionFOL(KB3)
    for step in result3:
        print(step)
    
if __name__ == "__main__":
    KB1 = {('FirstGrade',), ('~FirstGrade', 'Child'), ('~Child',)}
    print("ResolutionProp:")
    for line in ResolutionProp(KB1):
        print(line)
    print("\n")
    
    result1 = MGU('P(xx,a)', 'P(b,yy)')
    print(f"结果: {result1}")
    
    result2 = MGU('P(a,xx,f(g(yy)))', 'P(zz,f(zz),f(uu))')
    print(f"结果: {result2}")

    test_resolution_fol()