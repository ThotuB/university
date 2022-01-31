import { MongoClient } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';

export default async function handler(req: NextApiRequest, res: NextApiResponse) {
    if (req.method === 'GET') {
        const { userId } = req.query;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/users?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('admin');

        const result = await collection.findOne({ uid: userId });

        client.close()

        res.status(200).json(JSON.stringify(result));
    }
}
