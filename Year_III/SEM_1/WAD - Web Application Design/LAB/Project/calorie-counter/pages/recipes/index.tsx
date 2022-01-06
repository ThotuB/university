import Recipes from 'components/recipes/Recipes'
import Layout from 'components/layouts/navigation/Layout'
import axios from 'axios'

export default ({ recipes }) => {
    return (
        <Layout>
            <Recipes recipes={recipes} />
        </Layout>
    )
}

export async function getStaticProps() {
    const res = await axios.get('http://localhost:3000/api/recipes')
    // const client = await MongoClient.connect(
    //     'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
    // );
    // const db = client.db();

    // const collection = db.collection('recipes');

    // const recipes = await collection.find({}).toArray();

    // client.close();

    return {
        props: {
            recipes: res.data
        }
    }
}