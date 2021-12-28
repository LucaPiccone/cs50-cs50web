const questions = [
    {
        question: "What is the name of my dog?",
        options: ["Philip", "Rufus", "Isabella", "Easy"],
        answer: "Easy"
    },
    {
        question: "Where is the CN Tower?",
        options: ["Boston", "Montreal", "Seattle", "Toronto"],
        answer: "Toronto"
    },
    {
        question: "Where is Victoria Falls",
        options: ["Venezuela", "Denmark", "Canada", "Africa"],
        answer: "Africa"
    },
    {
        question: "When year was python first released?",
        options: ["1998", "1995", "1998", "1991"],
        answer: "1991"
    },
    {
        question: "What is the most popular programming language?",
        options: ["C#", "Java", "Python", "Javascript"],
        answer: "Javascript"
    }
];

let number_of_questions = questions.length;
let correct = 0;
let current_question = 0;

document.addEventListener('DOMContentLoaded', handleQuestion);

function handleQuestion() {
    document.querySelector('#question').innerHTML = questions[current_question].question

    let option = document.querySelector('#options')
    option.innerHTML = ''
    for (let i = 0, num_of_options = questions[current_question].options.length; i < num_of_options; i++)
    {
        option.innerHTML += `<button class="btn btn-secondary btn-sm m-1 optionBtns">${questions[current_question].options[i]}</button>`
    }

    document.querySelectorAll('.optionBtns').forEach((option) => {
        option.onclick = () => {
            if (option.textContent == questions[current_question].answer) {
                correct += 1;
                console.log('correct')
            }
            else
            {
                console.log('incorrect')
            }
            current_question += 1;
            document.querySelector('#correct').innerHTML = `${correct} of ${current_question}`
            let question_count = document.querySelector('#questionCount')
            question_count.innerHTML = `${current_question + 1} out of ${number_of_questions}`
            if (current_question == number_of_questions)
            {
                document.querySelector('#questionBox').innerHTML = `<div class="text-center"><h4>Quiz Complete</h4><h5>You scored ${correct} out of ${number_of_questions}</h5><div>`
                question_count.style.display = 'none';
            }
            else {
                handleQuestion();
            }
        }
    })
}

