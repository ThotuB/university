import FoodList from '../../components/food/food_list';
import Summary from '../../components/summary/summary';

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
        <div>
            <Summary />
            <FoodList items={dummy_foods}/>
        </div>
    );
}

export default Home;