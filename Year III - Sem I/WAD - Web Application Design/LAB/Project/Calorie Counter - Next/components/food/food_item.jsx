import Card from '../ui/card';
import Link from 'next/link';
import { useRouter } from 'next/router';

function FoodItem(props) {
    const router = useRouter();
    const { id, name, calories, company, author } = props;

    function handleClick() {
        router.push(`/food/${id}`);
    }

    return (
        <li>
            <Card>
                <div className="food-item">
                    {name} {calories} {company} {author}
                    <button onClick={handleClick}>
                        Details
                    </button>
                </div>
            </Card>
        </li>
    );
}

export default FoodItem;