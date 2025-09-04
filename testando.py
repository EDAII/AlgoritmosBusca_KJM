import tkinter as tk
from tkinter import messagebox, ttk
import math


def bubble_sort(data):
    arr = list(data)
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

def linear_search(data, target):
    for index, value in enumerate(data):
        if value == target:
            return f"Elemento {target} encontrado no índice {index}."
    return f"Elemento {target} não encontrado na lista."

def shell_sort(data):
    arr = list(data)
    n = len(arr)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = temp
        gap //= 2
    return arr

def hash_search(data, target):
    hash_table = {}
    for index, value in enumerate(data):
        if value not in hash_table:
            hash_table[value] = []
        hash_table[value].append(index)

    if target in hash_table:
        indices = hash_table[target]
        if len(indices) == 1:
            return f"Elemento {target} encontrado via Hash no índice {indices[0]}."
        else:
            return f"Elemento {target} encontrado via Hash nos índices: {', '.join(map(str, indices))}."
    else:
        return f"Elemento {target} não encontrado via Hash."

def indexed_search(data, target):
    sorted_list = sorted(data)
    n = len(sorted_list)

    if n == 0 or target < sorted_list[0] or target > sorted_list[-1]:
        return f"Elemento {target} não encontrado (fora do alcance da lista)."

    block_size = int(math.sqrt(n))
    if block_size == 0: block_size = 1
    
    guide_indices = [i for i in range(0, n, block_size)]
    guide_elements = [sorted_list[i] for i in guide_indices]

    for i in range(len(guide_elements) - 1):
        if guide_elements[i] <= target < guide_elements[i+1]:
            for j in range(guide_indices[i], guide_indices[i+1]):
                if sorted_list[j] == target:
                    return f"Elemento {target} encontrado no índice {j} da LISTA ORDENADA."
    
    for j in range(guide_indices[-1], n):
        if sorted_list[j] == target:
            return f"Elemento {target} encontrado no índice {j} da LISTA ORDENADA."

    return f"Elemento {target} não encontrado na lista."



# interface começa aqui:
class AlgorithmApp(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("Visualizador de Algoritmos")
        self.geometry("500x400")

        self.data = []
        self.algorithm_choice = tk.StringVar(value="bubble_sort")

        self.main_container = ttk.Frame(self, padding="10")
        self.main_container.pack(fill=tk.BOTH, expand=True)

        self.create_input_widgets()

    def create_input_widgets(self):
        for widget in self.main_container.winfo_children():
            widget.destroy()

        input_frame = ttk.LabelFrame(self.main_container, text="Passo 1: Insira os Dados", padding="10")
        input_frame.pack(fill=tk.X, pady=10)

        ttk.Label(input_frame, text="Digite números separados por vírgula (ex: 5, 3, 8, 1):").pack(anchor=tk.W)

        self.input_entry = ttk.Entry(input_frame)
        self.input_entry.pack(fill=tk.X, pady=5)
        self.input_entry.focus_set()

        submit_button = ttk.Button(input_frame, text="Confirmar Valores", command=self.process_input)
        submit_button.pack(pady=5)

    def process_input(self):
        input_str = self.input_entry.get()
        if not input_str:
            messagebox.showerror("Erro", "O campo de entrada não pode estar vazio.")
            return

        try:
            self.data = [int(item.strip()) for item in input_str.split(',')]
            self.create_algorithm_selection_widgets()
        except ValueError:
            messagebox.showerror("Erro de Formato", "Por favor, insira apenas números inteiros separados por vírgula.")

    def create_algorithm_selection_widgets(self):
        for widget in self.main_container.winfo_children():
            widget.destroy()

        data_display_frame = ttk.Frame(self.main_container)
        data_display_frame.pack(fill=tk.X, pady=(0, 15))
        ttk.Label(data_display_frame, text="Seus números:", font="-weight bold").pack(anchor=tk.W)
        ttk.Label(data_display_frame, text=str(self.data), wraplength=480).pack(anchor=tk.W)

        algorithm_selection_frame = ttk.LabelFrame(self.main_container, text="Passo 2: Escolha o Algoritmo", padding="10")
        algorithm_selection_frame.pack(fill=tk.X)

        ttk.Radiobutton(
            algorithm_selection_frame, text="Bubble Sort (Ordenação)", variable=self.algorithm_choice,
            value="bubble_sort", command=self.toggle_search_input
        ).pack(anchor=tk.W)

        ttk.Radiobutton(
            algorithm_selection_frame, text="Busca Linear (Pesquisa)", variable=self.algorithm_choice,
            value="linear_search", command=self.toggle_search_input
        ).pack(anchor=tk.W)

        ttk.Radiobutton(
            algorithm_selection_frame, text="Shell Sort (Ordenação)", variable=self.algorithm_choice,
            value="shell_sort", command=self.toggle_search_input
        ).pack(anchor=tk.W)

        ttk.Radiobutton(
            algorithm_selection_frame, text="Busca com Hash (Pesquisa)", variable=self.algorithm_choice,
            value="hash_search", command=self.toggle_search_input
        ).pack(anchor=tk.W)

        ttk.Radiobutton(
            algorithm_selection_frame, text="Busca Indexada (Pesquisa)", variable=self.algorithm_choice,
            value="indexed_search", command=self.toggle_search_input
        ).pack(anchor=tk.W)

        self.search_frame = ttk.Frame(algorithm_selection_frame, padding="5 0 0 0")
        self.search_frame.pack(fill=tk.X, padx=20, pady=5)
        ttk.Label(self.search_frame, text="Valor a ser buscado:").pack(side=tk.LEFT)
        self.search_entry = ttk.Entry(self.search_frame, width=10)
        self.search_entry.pack(side=tk.LEFT, padx=5)

        execute_button = ttk.Button(self.main_container, text="Executar Algoritmo", command=self.run_algorithm)
        execute_button.pack(pady=20)

        result_frame = ttk.LabelFrame(self.main_container, text="Resultado", padding="10")
        result_frame.pack(fill=tk.BOTH, expand=True)
        self.result_label = ttk.Label(result_frame, text="O resultado aparecerá aqui.", font="-size 10")
        self.result_label.pack()
        
        self.toggle_search_input()

    def toggle_search_input(self):
        search_algorithms = ["linear_search", "hash_search", "indexed_search"]
        if self.algorithm_choice.get() in search_algorithms:
            self.search_frame.pack(fill=tk.X, padx=20, pady=5)
        else:
            self.search_frame.pack_forget()

    def run_algorithm(self):
        choice = self.algorithm_choice.get()
        result = ""

        if choice == "bubble_sort":
            sorted_data = bubble_sort(self.data)
            result = f"Lista Ordenada: {sorted_data}"

        elif choice == "linear_search":
            try:
                target = int(self.search_entry.get())
                result = linear_search(self.data, target)
            except ValueError:
                messagebox.showerror("Erro", "Por favor, insira um número válido para a busca.")
                return
        
        elif choice == "shell_sort":
            sorted_data = shell_sort(self.data)
            result = f"Lista Ordenada (Shell Sort): {sorted_data}"

        elif choice == "hash_search":
            try:
                target = int(self.search_entry.get())
                result = hash_search(self.data, target)
            except ValueError:
                messagebox.showerror("Erro", "Por favor, insira um número válido para a busca.")
                return

        elif choice == "indexed_search":
            try:
                target = int(self.search_entry.get())
                result = indexed_search(self.data, target)
            except ValueError:
                messagebox.showerror("Erro", "Por favor, insira um número válido para a busca.")
                return

        self.result_label.config(text=result)


if __name__ == "__main__":
    app = AlgorithmApp()
    app.mainloop()
