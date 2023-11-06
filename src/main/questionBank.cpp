#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "questionBank.h"

std::vector<std::string> questions = {
	"In which process do plants release carbon dioxide?",
	"Is it true that the kidneys are part of the digestive system?",
	"What type of cell is characterized by a permanent vacuole?",
	"What is the only liquid metal?",
	"What do we call a substance that changes the rate of a chemical reaction?",
	"The 'Garbage Patch' in the Pacific Ocean is mainly composed of what material?",
	"Are solar panels a renewable source of energy?",
	"Which is the first country with a negative carbon footprint?",
	"What is the process of nutrition in plants called?",
	"Which chemical element is used as fuel in nuclear power plants?",
	"What is the process of the division of sex cells called?",
	"What substances are used as a reserve source of energy in the human body?",
	"Antibiotics are used against which type of infections?",
	"What is the chemical name for ethyl alcohol?",
	"What is the agreement among EU countries for climate preservation called?",
	"Which type of vehicles are the most environmentally friendly?",
	"What is the process of carbon dioxide accumulation in the atmosphere called?",
	"What element are diamonds and graphite made of?",
	"Which country is Greta Thunberg, the eco-activist, from?",
	"Which country has the highest air pollution levels?",
	"What is the only liquid non-metal?",
	"What chemical element has atomic number Z (Z = 1)?",
	"What is the crystal lattice of the compound sodium chloride (NaCl) like?",
	"Which element is most abundant in the Earth's atmosphere?",
	"Is it true that the general formula for alkanes is C(n)H(2n+2)?",
	"Is it true that we can extract energy from the oceans?",
	"How many diatomic molecules exist in chemistry?",
	"Which chemical element is primarily used in making batteries?",
	"Who laid the foundations of genetics?",
	"What plant did Mendel experiment on?",
	"Which supramolecular complex is simultaneously living and dead?",
	"What is the cellular structure that carries genetic information called?",
	"How many chromosomes do humans have?",
	"How many main types of plastids are there in plants?",
	"Which chemical element is most abundant in the human body?",
	"Which chemical compound is most abundant in the human body?",
	"Which cell organelle is known as the cell's powerhouse?",
	"How many types of endoplasmic reticulum exist?",
	"Which chemical compound protects the Earth from harmful solar radiation?",
	"How many years does it take for a nylon bag to decompose?",
	"Open-pit or underground mines lead to more environmental problems?",
	"What is the largest coal mining region in Western Europe?",
	"What is the process of chemical interaction between an acid and a base called?",
	"What is the chemical name for caustic soda?",
	"What is the oldest natural park in the Balkans?",
	"What is the oldest national park in Bulgaria?",
	"With the count of which charged particles of a chemical element can we determine its atomic number?",
	"What do we determine by counting the number of electron shells of a chemical element?",
	"What do we determine by counting the number of electrons in the outermost electron shell?",
	"Ions are positively, negatively, or neutrally charged?"
};

std::vector<std::string> answers = {
	"Respiration",
	"No",
	"Plant cell",
	"Mercury",
	"Catalyst",
	"Plastic",
	"Yes",
	"Bhutan",
	"Photosynthesis",
	"Uranium",
	"Meiosis",
	"Fats",
	"Bacterial",
	"Ethanol",
	"Green Deal",
	"Electric cars",
	"Global warming",
	"Carbon",
	"Sweden",
	"China",
	"Bromine",
	"Hydrogen",
	"Ionic",
	"Nitrogen",
	"Yes",
	"Yes",
	"7",
	"Lithium",
	"Gregor Mendel",
	"Peas",
	"Virus",
	"Chromosome",
	"46",
	"3",
	"Carbon",
	"Water",
	"Mitochondria",
	"2",
	"Ozone",
	"55",
	"Open-pit",
	"Ruhr",
	"Neutralization",
	"NaOH",
	"Vitosha",
	"Pirin",
	"Protons",
	"The period",
	"The group",
	"No"
};

void question(bool& checkAnswer) {
	int random;
	std::string playerAnswer;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, 48);
	random = distribution(gen);

	std::cout << std::endl;
	std::cout << "Your question is: " << questions[random] << std::endl;
	std::getline(std::cin, playerAnswer);

	if (playerAnswer == answers[random]) {
		std::cout << "Congratulations! Your answer is correct! You may continue the game!" << std::endl;
		checkAnswer = true;
	}

	else {
		std::cout << "Sorry, your answer is incorrect! Your bird is burnt! Try again!" << std::endl;
		std::cout << "The correct answer to your question was: " << answers[random] << std::endl;
		checkAnswer = false;
	}
}