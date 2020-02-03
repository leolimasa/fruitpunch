from fruitpunch.native.common.observer import Observer


class FunctionObserver(Observer):
    def __init__(self, function):
        super(FunctionObserver, self).__init__()
        
        self.function = function
            
    def action(self, event):
        if not hasattr(event, "source"):
            event.source = self.instance
        self.function(event)