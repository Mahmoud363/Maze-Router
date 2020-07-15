

class Pin:

    # default constructor
    def __init__(self, layer=0, x=0, y=0, _id='', pre=None):
        self.layer = layer
        self.x = layer
        self.y = layer
        self.id=_id
        self.pre = pre 

