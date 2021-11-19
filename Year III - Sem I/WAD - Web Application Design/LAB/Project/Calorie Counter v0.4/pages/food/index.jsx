import FoodList from '../../components/food/FoodList';
import Summary from '../../components/goal/Summary';
import Pagination from '../../components/pagination/Pagination';
import Layout from '../../components/layout/navigation/Layout';


const dummy_foods = [
    {
        id: 1,
        name: 'Pizza',
        macros: {
            carbs: 10,
            protein: 10,
            fat: 20
        },
        calories: 400,
        company: 'Dominos',
        author: 'Thotu',
        rating: 4.5
    },
    {
        id: 2,
        name: 'Burgir',
        macros: {
            carbs: 12,
            protein: 15,
            fat: 20
        },
        calories: 500,
        company: 'Mc',
        author: 'Thotu',
        rating: 3.7
    },
    {
        id: 3,
        name: 'Burgir',
        macros: {
            carbs: 12,
            protein: 15,
            fat: 20
        },
        calories: 500,
        company: 'Mc',
        author: 'Thotu',
        rating: 1.2
    },
    {
        id: 4,
        name: 'Burgir',
        macros: {
            carbs: 12,
            protein: 15,
            fat: 20
        },
        calories: 500,
        company: 'Mc',
        author: 'Thotu',
        rating: 3
    },
    {
        id: 5,
        name: 'Burgir',
        macros: {
            carbs: 12,
            protein: 15,
            fat: 20
        },
        calories: 500,
        company: 'Mc',
        author: 'Thotu',
        rating: 3
    },
    {
        id: 6,
        name: 'Burgir',
        macros: {
            carbs: 12,
            protein: 15,
            fat: 20
        },
        calories: 500,
        company: 'Mc',
        author: 'Thotu',
        rating: 3
    }
];

function Home() {
    return (
        <Layout>
            <div className="flex flex-col gap-6">
                <Summary />
                <FoodList items={dummy_foods}/>
                <Pagination />
            </div>
        </Layout>
    );
}

export default Home;