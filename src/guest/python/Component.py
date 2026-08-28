from wit.wit_world import exports

class Info(exports.Info):
    def get_message(self, number: int) -> str:
        return f'This is Python functon, number = {number}'
