# 1: Transaction Database Creation
def defineTransaction():
    transactions = [
        "T1 a b c e",
        "T2 b d f",
        "T3 a c d f",
        "T4 d f",
        "T5 c d e"
    ]
    with open("Lab1_output.txt", "w") as file:
        for transaction in transactions:
            file.write(transaction + "\n")
    print("\nTransaction database created and stored in Lab1_output.txt.")

# Read from the files
def readTransaction():
    with open("Lab1_output.txt", "r") as file:
        transactions = [line.strip() for line in file]
    
    print("\nRead successfully")
    return (transactions)


# Item Support / Count
def find_item_support(data):
    item_count = {}
    for transaction in data:
        items = transaction.split()[1:]
        for item in items:
            item_count[item] = item_count.get(item, 0) + 1
    print(item_count)

# Extract Item List
def extract_item_transaction_list(data):

    item_transaction_list = {}

    for i, transaction in enumerate(data, start=1):
        items = transaction.split()[1:]
        for item in items:
            if item not in item_transaction_list:
                item_transaction_list[item] = []
            item_transaction_list[item].append(f"T{i}")

    print (item_transaction_list)

import random
# Generate Random Transaction and its elements
def generate_random_transactions(transactions, num_transactions):
    random_transactions = []
    num_items = len(set(item for transaction in transactions for item in transaction.split()[1:]))

    for _ in range(num_transactions):
        random_transaction = []
        num_items_in_transaction = random.randint(1, num_items)
        random_items = random.sample(range(1, num_items + 1), num_items_in_transaction)

        for item_index in random_items:
            item = list(set(item for transaction in transactions for item in transaction.split()[1:]))[item_index - 1]
            random_transaction.append(item)

        random_transactions.append(f"T{len(transactions) + len(random_transactions) + 1} {' '.join(random_transaction)}")
    print(random_transactions)
    with open("Lab1_output.txt", "a") as file:
        for transaction in random_transactions:
            file.write(transaction + "\n")

# Calling the functions
defineTransaction()
data = []
data = readTransaction()
find_item_support(data)
extract_item_transaction_list(data)
generate_random_transactions(data, 5)