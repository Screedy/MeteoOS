import utime
import gc


def execution_time(func):
    """Decorator to measure the execution time of a function."""

    def wrapper(*args, **kwargs):
        start = utime.ticks_us()
        result = func(*args, **kwargs)
        end = utime.ticks_us()
        exec_time = utime.ticks_diff(end, start) / 1_000_000    # Convert to seconds

        print(f"Execution time of {func.__name__} is {exec_time:.5f} seconds.")
        return result

    return wrapper


def ram_usage(func):
    """Decorator to measure the RAM usage of a function."""

    def wrapper(*args, **kwargs):
        gc.collect()                # Collect garbage before running the function
        start_mem = gc.mem_free()   # Get the free memory before running the function
        result = func(*args, **kwargs)
        end_mem = gc.mem_free()     # Get the free memory after running the function

        print(f"RAM usage before {func.__name__}: {start_mem} bytes\n RAM usage after {func.__name__}: {end_mem}.")
        print(f"The difference was {start_mem - end_mem} bytes.")
        return result

    return wrapper
