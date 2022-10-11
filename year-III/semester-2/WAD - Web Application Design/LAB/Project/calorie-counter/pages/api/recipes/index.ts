import { MongoClient } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';

export default async function handler(req: NextApiRequest, res: NextApiResponse) {
    if (req.method === 'GET') {
        const { pageNumber, pageSize, userId } = req.query;
        const page = parseInt(pageNumber as string, 10) || 0;
        const size = parseInt(pageSize as string, 10) || 10;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('recipes');

        const result = await collection
            .find(userId ? { "user.id": userId } : {})
            .skip(page > 0 ? (page - 1) * size : 0)
            .limit(size)
            .toArray();
        const total = await collection.countDocuments();

        client.close()

        res.status(200).json({
            entries: total,
            pages: Math.ceil(total / size),
            recipes: result.map(recipe => {
                return {
                    id: recipe._id.toString(),
                    name: recipe.name,
                    description: recipe.description,
                    image: recipe.image,
                    approved: recipe.approved,
                    user: {
                        id: recipe.user.id,
                        name: recipe.user.name,
                        image: recipe.user.image
                    }
                }
            })
        })
    }

    if (req.method === 'POST') {
        const data = req.body;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/recipes?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('recipes');

        const result = await collection.insertOne(data)

        console.log(result)

        client.close()

        res.status(201).json({
            message: 'Recipe added',
        })
    }
}
