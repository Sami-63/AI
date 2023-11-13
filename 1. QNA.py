
def findans(question: str):
	question_words = [word.lower() for word in question.split()]
	question_words = set(question_words)

	ret = []
	with open("q.txt", "r") as file:
		lines = file.read().split('\n')

		for line in lines:
			line_words = [word.lower() for word in line.split() ]
			line_words = set(line_words)

			cnt = 0
			for word in line_words:
				if word in question_words:
					cnt += 1

			ret.append([cnt, line])

	ret.sort(reverse=True)
	if len(ret):
		return ret[0][1]

	return "Sorry, I don't have an answer for that."

while True:
    question = input("Ask me a question. Type 'exit' to stop: ")
    if question.lower() == 'exit':
        break

    print(findans(question))
