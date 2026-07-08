class BaseService:

    def __init__(self, cache, uow):
        self.cache = cache
        self.uow = uow