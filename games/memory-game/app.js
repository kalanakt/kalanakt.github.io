const cordArray = [
    {
        name: 'fries',
        img: 'images/fries.png'
    },
    {
        name: 'chesebuger',
        img: 'images/cheeseburger.png'
    },
    {
        name: 'ice-cream',
        img: 'images/ice-cream.png'
    },
    {
        name: 'hotdog',
        img: 'images/hotdog.png'
    },
    {
        name: 'milkshake',
        img: 'images/milkshake.png'
    },
    {
        name: 'pizza',
        img: 'images/pizza.png'
    },
    {
        name: 'fries',
        img: 'images/fries.png'
    },
    {
        name: 'chesebuger',
        img: 'images/cheeseburger.png'
    },
    {
        name: 'ice-cream',
        img: 'images/ice-cream.png'
    },
    {
        name: 'hotdog',
        img: 'images/hotdog.png'
    },
    {
        name: 'milkshake',
        img: 'images/milkshake.png'
    },
    {
        name: 'pizza',
        img: 'images/pizza.png'
    }    
]

cordArray.sort(() => 0.5 - Math.random())

const gridDisplay = document.querySelector('#grid')
const resultDisplay = document.querySelector('#result')
let cardChosen = []
let cardChosenids = []
const cardWon = []

function createBoard (){
    for (let i = 0; i < cordArray.length; i++){
        const card = document.createElement('img')
        card.setAttribute('src', "images/blank.png")
        card.setAttribute('data-id', i)
        card.addEventListener('click', flipCard)
        gridDisplay.appendChild(card)
    }
}
createBoard ()

function checkMatch(){
    const cards = document.querySelectorAll('img')
    const opetionOneId = cardChosenids[0]
    const opetionTwoId = cardChosenids[1]
    console.log(cards)
    console.log('check Match...')
    if (opetionOneId == opetionTwoId) {  
        cards[opetionOneId].setAttribute('src','images/blank.png')
        cards[opetionTwoId].setAttribute('src','images/blank.png')   
        alert('you clicked same card !!!')
    }
    if (cardChosen[0] == cardChosen[1]) {
        alert('You Found Match')
        cards[opetionOneId].setAttribute('src','images/white.png')
        cards[opetionTwoId].setAttribute('src','images/white.png')
        cards[opetionOneId].removeEventListener('click', flipCard)
        cards[opetionTwoId].removeEventListener('click', flipCard)
        cardWon.push(cardChosen)
    } else {
        cards[opetionOneId].setAttribute('src','images/blank.png')
        cards[opetionTwoId].setAttribute('src','images/blank.png')
        alert('Try Again !!!')
    }
    cardChosen = []
    cardChosenids = []

    resultDisplay.textContent = cardWon.length

    if (cardWon.length == (cordArray.length / 2)) {
        resultDisplay.innerHTML = 'Congratulation You Find Them All'
    }
}

function flipCard(){
    let cardId = this.getAttribute('data-id')
    cardChosen.push(cordArray[cardId].name)
    cardChosenids.push(cardId)
    console.log(cardChosen)
    this.setAttribute('src', cordArray[cardId].img) 
    
    if ( cardChosen.length == 2){
        setTimeout(checkMatch, 500)     
    }
}