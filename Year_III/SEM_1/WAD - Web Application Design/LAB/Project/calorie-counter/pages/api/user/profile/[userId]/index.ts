import { MongoClient, ObjectId } from 'mongodb';
import { NextApiRequest, NextApiResponse } from 'next';

export default async function handler(req: NextApiRequest, res: NextApiResponse) {
    if (req.method === 'GET') {
        const { userId } = req.query;

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/users?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('profile');

        const result = await collection.findOne({ uid: userId });

        client.close()

        res.status(200).json(JSON.stringify(result));
    }

    if (req.method === 'PUT') {
        const { userId } = req.query;
        const { name, email, phone, image, website, bio, gender, isAdmin } = req.body

        const client = await MongoClient.connect(
            'mongodb+srv://admin:WF0qDFsvY6ux716Q@thotu.lmwwa.mongodb.net/users?retryWrites=true&w=majority'
        );
        const db = client.db();

        const collection = db.collection('profile');

        const result = await collection.updateOne({ uid: userId }, {
            $set: {
                name,
                email,
                phone,
                image,
                website,
                bio,
                gender,
                isAdmin,
            }
        })

        client.close()

        if (!result) {
            res.status(404)
            return;
        }

        res.status(200).json({
            message: "Profile updated"
        });
    }
}
