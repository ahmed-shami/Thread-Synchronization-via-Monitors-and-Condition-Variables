<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <title>BENSCHILLIBOWL Thread Synchronization Project</title>
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <style>
    body { font-family: system-ui, -apple-system, Segoe UI, Roboto, Arial, sans-serif; line-height: 1.5; margin: 2rem; color: #111; }
    code, pre { font-family: ui-monospace, SFMono-Regular, Menlo, Consolas, "Liberation Mono", monospace; }
    pre { background: #f6f8fa; padding: 1rem; border-radius: 6px; overflow: auto; }
    h1, h2 { margin-top: 1.6rem; }
    ul { margin: 0.5rem 0 1rem 1.25rem; }
    .k { color: #0550ae; font-weight: 600; }
  </style>
</head>
<body>

  <h1>BENSCHILLIBOWL Thread Synchronization Project</h1>

  <h2>Overview</h2>
  <p>
    This program simulates customers and cooks using POSIX threads, a mutex, and condition variables.
    Customers add orders to a shared queue. Cooks take orders from the queue and fulfill them.
    The program exits when all expected orders are handled.
  </p>

  <h2>Files</h2>
  <ul>
    <li><span class="k">main.c</span> creates customer and cook threads, starts the restaurant, joins threads, and shuts down.</li>
    <li><span class="k">BENSCHILLIBOWL.c</span> implements the restaurant queue and synchronization.</li>
    <li><span class="k">BENSCHILLIBOWL.h</span> provides structs and function prototypes. Do not modify this file.</li>
    <li><span class="k">Makefile</span> builds, runs, and cleans the project.</li>
  </ul>

  <h2>Build</h2>
  <pre><code>make
</code></pre>

  <h2>Run</h2>
  <pre><code>./benschillibowl
</code></pre>

  <h2>Clean</h2>
  <pre><code>make clean
</code></pre>

  <h2>Expected Output</h2>
  <p>You should see lines like:</p>
  <pre><code>Restaurant is open!
Cook #0 fulfilled 111 orders
...
Restaurant is closed!
</code></pre>
  <p>
    The sum of all fulfilled orders equals
    <code>NUM_CUSTOMERS * ORDERS_PER_CUSTOMER</code>.
  </p>

  <h2>How It Works</h2>
  <ul>
    <li>Customers allocate an <code>Order</code>, pick a random menu item, set <code>customer_id</code>, then call <code>AddOrder</code>.</li>
    <li>Cooks loop on <code>GetOrder</code>, count fulfilled orders, and <code>free(order)</code>.</li>
    <li>A mutex protects shared data in the restaurant struct.</li>
    <li>Condition variables:
      <ul>
        <li><code>can_add_orders</code> waits when the queue is full.</li>
        <li><code>can_get_orders</code> waits when the queue is empty.</li>
      </ul>
    </li>
    <li>When all expected orders are handled, <code>GetOrder</code> returns <code>NULL</code> and cooks exit.</li>
  </ul>

  <h2>Tuning</h2>
  <p>Edit these in <code>main.c</code> and rebuild:</p>
  <ul>
    <li><code>NUM_CUSTOMERS</code></li>
    <li><code>NUM_COOKS</code></li>
    <li><code>ORDERS_PER_CUSTOMER</code></li>
    <li><code>BENSCHILLIBOWL_SIZE</code></li>
  </ul>

  <h2>Notes</h2>
  <ul>
    <li>Do not change <code>BENSCHILLIBOWL.h</code>.</li>
    <li>Every allocated <code>Order</code> must be freed by a cook.</li>
    <li>Use sanitizers or Valgrind if you want to check for data races or memory leaks.</li>
  </ul>

</body>
</html>
