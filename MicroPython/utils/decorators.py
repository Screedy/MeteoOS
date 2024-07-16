import time


def execution_time(func):
    """Decorator to measure the execution time of a function."""

    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()

        print(f"Execution time of {func.__name__} is {end-start:.8f}s")
        return result

    return wrapper
