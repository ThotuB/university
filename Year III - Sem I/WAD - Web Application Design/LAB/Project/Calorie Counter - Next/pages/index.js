import FoodList from '../components/food/food_list';

const dummy_foods = [
    {
        id: 1,
        name: 'Pizza',
        calories: 400,
        company: 'Dominos',
        author: 'Thotu'
    },
    {
        id: 2,
        name: 'Burgir',
        calories: 500,
        company: 'Mc',
        author: 'Thotu'
    }
];

function Home() {
    return (
        <>
            <h1>Home</h1>
            <FoodList items={dummy_foods}/>
        </>
    );
}

export default Home;