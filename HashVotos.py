class VotingSystem:
    def __init__(self):
        self.voter_ids = set()  # Armazena IDs dos eleitores que já votaram
        self.votes = {}  # Contabiliza os votos dos candidatos

    def vote(self, voter_id, candidate):
        if voter_id in self.voter_ids:
            return "Erro: Eleitor já votou."
        else:
            self.voter_ids.add(voter_id)  # Marca o eleitor como tendo votado
            if candidate in self.votes:
                self.votes[candidate] += 1
            else:
                self.votes[candidate] = 1
            return f"Voto registrado para {candidate}!"

    def show_results(self):
        if not self.votes:
            return "Nenhum voto registrado ainda."
        results = "Resultado da eleição:\n"
        for candidate, count in sorted(self.votes.items(), key=lambda x: (-x[1], x[0])):
            results += f"{candidate}: {count} voto(s)\n"
        return results.strip()


# Exemplo de uso
election = VotingSystem()

# Eleitor votando pela primeira vez
print(election.vote("123", "Alice"))  # Saída: "Voto registrado para Alice!"

# Eleitor tentando votar novamente
print(election.vote("123", "Bob"))  # Saída: "Erro: Eleitor já votou."

# Outro eleitor votando
print(election.vote("456", "Bob"))  # Saída: "Voto registrado para Bob!"

# Exibindo o resultado da eleição
print(election.show_results())