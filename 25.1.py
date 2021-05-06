import time
from z3 import *

Registers_State=Datatype ('Registers_State')
Registers_State.declare('cons', ('A', BitVecSort(16)), ('B', BitVecSort(16)))
Registers_State=Registers_State.create()

Operation, (OP_MULT, OP_MINUS, OP_PLUS, OP_XOR, OP_OR, OP_AND) = EnumSort('Operation', ('OP_MULT', 'OP_MINUS', 'OP_PLUS', 'OP_XOR', 'OP_OR', 'OP_AND'))

Register, (A, B) = EnumSort('Register', ('A', 'B'))

# Register, Registers_State -> int
def register_selector (register, input_registers):
    return If(register==A, Registers_State.A(input_registers),
           If(register==B, Registers_State.B(input_registers), 
              0))

# Bool, Register, Registers_State, int -> int
def register_or_constant_selector (register_or_constant, register, input_registers, constant): 
    return If(register_or_constant==False, register_selector(register, input_registers), constant)

# Operation, Bool, Register, Register, Int, Registers_State -> int
def one_op (op, register_or_constant, reg1, reg2, constant, input_registers):
    arg1=register_selector(reg1, input_registers)
    arg2=register_or_constant_selector (register_or_constant, reg2, input_registers, constant)
    return If(op==OP_MULT,   arg1*arg2,
           If(op==OP_MINUS,  arg1-arg2,
           If(op==OP_PLUS,   arg1+arg2, 
           If(op==OP_XOR,    arg1^arg2, 
           If(op==OP_OR,     arg1|arg2, 
           If(op==OP_AND,    arg1&arg2, 
                          0)))))) # default

# Bool, Register, Operation, Register, Register, Int, Registers_State -> Registers_State
def one_step (register_or_constant, register_assigned_in_this_step, op, reg1, reg2, constant, input_registers):
    new_val=one_op(op, register_or_constant, reg1, reg2, constant, input_registers)
    return If (register_assigned_in_this_step==A, Registers_State.cons(new_val,
                                                                       Registers_State.B(input_registers)),
           If (register_assigned_in_this_step==B, Registers_State.cons(Registers_State.A(input_registers), 
                                                                       new_val), 
                                                  Registers_State.cons(0,0))) # default
              
def program(input_registers, STEPS):
    cur_input=input_registers
    for x in range(STEPS):
        cur_input=one_step (reg_or_constant_step[x], reg_step[x], op_step[x], reg1_step[x], reg2_step[x], constant_step[x], cur_input)
    return cur_input

def print_one_step (m, step):
    op_in_model=str(m[op_step[step]])

    if op_in_model=='OP_PLUS':
        tmp_str="+"
    elif op_in_model=='OP_MINUS':
        tmp_str="-"
    elif op_in_model=='OP_MULT':
        tmp_str="*"
    elif op_in_model=='OP_XOR':
        tmp_str="^"
    elif op_in_model=='OP_OR':
        tmp_str="|"
    elif op_in_model=='OP_AND':
        tmp_str="&"
    else:
        raise AssertionError

    if is_true(m[reg_or_constant_step[step]]):
        print (m[reg_step[step]],"=",m[reg1_step[step]],tmp_str,m[constant_step[step]])
    else:
        print (m[reg_step[step]],"=",m[reg1_step[step]],tmp_str,m[reg2_step[step]])

def try_for_n_steps (STEPS, constraints_to_use, constraints):
    s=Solver()

    global op_step, reg_or_constant_step, reg_step, reg1_step, reg2_step, constant_step

    op_step=[Const('op_step%s' % i, Operation) for i in range(STEPS)]
    reg_or_constant_step=[Bool('reg_or_constant_step%s' % i) for i in range(STEPS)]
    reg_step=[Const('reg_step%s' % i, Register) for i in range(STEPS)]
    reg1_step=[Const('reg1_step%s' % i, Register) for i in range(STEPS)]
    reg2_step=[Const('reg2_step%s' % i, Register) for i in range(STEPS)]
    constant_step = [BitVec('constant_step%s' % i, 16) for i in range(STEPS)]

    for x in range(STEPS):
        s.add (constant_step[x]>=0, constant_step[x]<=63)

    for i in constraints[:constraints_to_use]:
        s.add (program(Registers_State.cons(i[0][0], i[0][1]), STEPS)==Registers_State.cons(i[1][0], i[1][1]))

    start_t=time.time()

    tmp=s.check()
    if tmp==sat:
        print ("sat!")
        m=s.model()
        #print m
        for x in range(STEPS):
            print_one_step (m, x)
        rt=True
    else:
        print (tmp)
        rt=False

    print ("seconds spent: ", int(time.time()-start_t))
    return rt
    
file1 = open("G:/crackmes/challenges.re writeup/25.1.txt", 'r')
constraints_from_file = []
for line in file1:
    constraints_from_file.append(((int(line[2:8], 16),0), (int(line[17:-1],16),0)))

for steps in range(1, 8):
    constraints_to_use=8
    print ("Trying to find %d-step(s) program using %d input/output pairs" % (steps, constraints_to_use))
    if try_for_n_steps (steps, constraints_to_use, constraints_from_file):
        break
