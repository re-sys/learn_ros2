from demo_python_pkg.person_node import PersonNode

class WriterNode(PersonNode):
    def __init__(self,name_val:str,age_val:int,book:str)->None:
        self.book = book
        super().__init__(name_val,age_val)
    
def main():
    writer = WriterNode("Jane Doe",30,"The Great Gatsby")
    writer.eat("something ")